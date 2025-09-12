/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/12 17:11:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	convert_errno(int err)  // convertir le errno vers un code de retour valable
{
	if (err == ENOENT)
		return (127);
	if (err == EACCES || err == EISDIR)
		return (126);
	return (1);
}

static int	execute_fork(t_minishell_p shell, t_ast_p ast)
{
	pid_t	*pid;
	int		errnum;
	int		return_status;

	ast->leaf->pid = fork();
	if (ast->leaf->pid == -1)
	{
		;	// sequence erreur
	}
	if (ast->leaf->pid == 0)
	{
		if (ast->leaf->fds[0] == -1 || ast->leaf->fds[1] == -1)
			exit(convert_errno(ENOENT));
		redirect_leaf(ast);
		close_fds(ast->leaf);
		execve(*ast->leaf->cmds, ast->leaf->cmds, shell->environ);
		errnum = errno;
		print_cmd_error(ast->leaf->command_name, errnum);
		exit(convert_errno(errnum));
	}
	else
	{
		close_fds(ast->leaf);
		waitpid(ast->leaf->pid, &return_status, 0);
		return (return_status);
	}
}

int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;
	int		return_status;

	if (!ast->leaf->configured)
		preconfig_leaf(shell, ast->leaf);
	if (is_builtin(ast->leaf))
		return_status = execute_builtin(shell, ast->leaf);
	else
		return_status = execute_fork(shell, ast);
	return (return_status);
}
