/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/10 21:28:51 by sosony           ###   ########.fr       */
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
			close_fds(ast, CHILD);
			wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
			exit(shell->exit_code);
		}
		else if (pid > 0)
		{
			close_fds(ast, PARENT);
			if (ast->cntl_op->left && ast->cntl_op->left->type == OP_PIPE)
			{
				close_secure(ast->cntl_op->left->closed_fd);
			}
			waitpid(pid, &shell->exit_code, 0);
		}
	}
}
