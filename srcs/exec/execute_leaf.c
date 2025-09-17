/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:22:23 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	convert_errno(int err)
{
	if (err == ENOENT)
		return (127);
	if (err == EACCES || err == EISDIR)
		return (126);
	return (1);
}

static void	_execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	int		errnum;
	int		access_value;

	if (ast->leaf->fds[0] == -1 || ast->leaf->fds[1] == -1)
		exit(convert_errno(ENOENT));
	redirect_leaf(shell, ast);
	close_fds(ast, CHILD);
	if (ast->leaf->abort == true)
		exit(EXIT_FAILURE);
/* 	else if (!*ast->leaf->cmds)
	{
		exit(EXIT_SUCCESS);			// cas par exemple de la commande "<< eof"
	} */
	else
	{
		execve(*ast->leaf->cmds, ast->leaf->cmds, shell->environ);
		errnum = errno;
		print_cmd_error(shell, ast->leaf->name, errnum);
		exit(convert_errno(errnum));
	}
}

static void	execute_command(t_minishell_p shell, t_ast_p ast)
{
	pid_t	*pid;

	ast->leaf->pid = fork();
	if (ast->leaf->pid == -1)
	{
		;
	}
	if (ast->leaf->pid == 0)
	{
		_execute_leaf(shell, ast);
	}
	else
	{
		close_fds(ast, PARENT);
	}
}

void	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;

	if (!ast->leaf->configured)
		preconfig_leaf(shell, ast->leaf);
	if (is_builtin(ast->leaf))
		execute_builtin(shell, ast->leaf);
	else
		execute_command(shell, ast);
}
