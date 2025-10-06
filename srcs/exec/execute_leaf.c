/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/06 18:22:02 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_path(char *path)
{
	struct stat	file_stats;

	if (!path)
		return (ENOENT);
	if (ft_strchr(path, '/'))
	{
		if (stat(path, &file_stats) != 0)
			return (ENOENT);
		if (S_ISDIR(file_stats.st_mode))
			return (EISDIR);
		if (access(path, X_OK) != 0)
			return (EACCES);
		return (0);
	}
	return (ENOENT);
}

static void	_execve(t_minishell_p shell, t_ast_p ast)
{
	int	errnum;

	if (is_no_abort(shell))
	{
		errnum = check_path(ast->leaf->exec_path);
		if (errnum)
		{
			print_cmd_error(shell, *ast->leaf->cmds, errnum);
			exit(convert_errno(errnum));
		}
		else
		{
			execve(ast->leaf->exec_path, ast->leaf->cmds, shell->environ);
			print_cmd_error(shell, *ast->leaf->cmds, errno);
			exit(convert_errno(errno));
		}		
	}
}

static void	_execute_command(t_minishell_p shell, t_ast_p ast)
{
	if (redirect_leaf(shell, ast) == -1)
		exit(EXIT_FAILURE);
	close_fds(ast, CHILD);
	if (!*ast->leaf->cmds)
		exit(EXIT_SUCCESS);
	else
		_execve(shell, ast);
}

static void	execute_command(t_minishell_p shell, t_ast_p ast)
{
	ast->leaf->pid = _fork(shell);
	if (ast->leaf->pid == 0)
	{
		signals_dfl();
		_execute_command(shell, ast);
	}
	else if (ast->leaf->pid > 0)
	{
		signals_ign();
		close_fds(ast, PARENT);
	}
}

void	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		pipeline_expand(shell, ast);
		wildcard_expand(shell, ast);
		ast->leaf->full_path = find_cmd(shell, ast);
		if (is_no_abort(shell))
		{
			if (is_builtin(ast->leaf))
				execute_builtin(shell, ast);
			else
				execute_command(shell, ast);			
		}
	}
}
