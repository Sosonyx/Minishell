/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/30 17:47:33 by cgajean          ###   ########.fr       */
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

	errnum = check_path(ast->leaf->full_path);
	if (errnum)
	{
		print_cmd_error(shell, *ast->leaf->cmds, errnum);
		exit(convert_errno(errnum)); // clean exit surement ici
	}
	execve(ast->leaf->full_path, ast->leaf->cmds, shell->environ);
	print_cmd_error(shell, *ast->leaf->cmds, errno);
	exit(convert_errno(errno));
}

static void	_execute_command(t_minishell_p shell, t_ast_p ast)
{
	redirect_leaf(shell, ast);
	close_fds(ast, CHILD);
	if (ast->leaf->abort == true)
		exit(EXIT_FAILURE);
	if (!*ast->leaf->cmds)
		exit(EXIT_SUCCESS);
	_execve(shell, ast);
}

static void	execute_command(t_minishell_p shell, t_ast_p ast)
{
	ast->leaf->pid = fork();
	if (ast->leaf->pid == -1)
		set_abort(shell, FORK_ERRMSG);
	else if (ast->leaf->pid == 0)
		_execute_command(shell, ast);
	else
		close_fds(ast, PARENT);
}

int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	variable_expand(shell, ast);
	ast->leaf->full_path = find_cmd(ast->leaf->cmds[0], shell->environ);
	wildcard_expand(&ast->leaf->cmds);
	if (is_builtin(ast->leaf))
	{
		execute_builtin(shell, ast);	
		return (shell->last_status);
	}
	else
		execute_command(shell, ast);
	return (shell->abort == false);
}
