/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/09 20:24:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_subshell(t_shell_p shell, t_ast_p ast)
{
	pid_t	pid;

	if (is_no_abort(shell))
	{
		pid = _fork(shell);
		if (pid == 0)
		{
			forward_fds(ast);
			_execute_ast(shell, ast->cntl_op->left);
/* 			close_secure(ast->read_fd);
			close_secure(ast->closed_fd); */

			close_fds(ast, CHILD);

			wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
			exit(shell->exit_code);
		}
		else if (pid > 0)
		{
			close_fds(ast, PARENT);
			waitpid(pid, &shell->exit_code, 0);
		}
	}
}
