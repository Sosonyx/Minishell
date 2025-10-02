/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/02 16:31:18 by ihadj            ###   ########.fr       */
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
		wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
		exit(shell->exit_code);
	}
	else if (pid > 0)
	{
		close_fds(ast, PARENT);
		waitpid(pid, &shell->exit_code, 0);
	}
	else
	{
		set_abort(shell, FORK_ERRMSG);
		shell->exit_code = EXIT_FAILURE;
	}
}
