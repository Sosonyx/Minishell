/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/01 12:54:29 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	pid_t	pid;

	forward_fds(ast);

	pid = fork();
	if (pid == 0)
	{
		_execute_ast(shell, ast->cntl_op->left);
		wait_if_leaf(ast->cntl_op->left->leaf, &g_status);
		exit(g_status);
	}
	else if (pid > 0)
	{
		close_fds(ast, PARENT);
		waitpid(pid, &g_status, 0);
	}
	else
	{
		set_abort(shell, FORK_ERRMSG);
		g_status = EXIT_FAILURE;
	}
}
