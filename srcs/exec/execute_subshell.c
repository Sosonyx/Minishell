/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/13 17:11:17 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_subshell(t_shell_p shell, t_ast_p ast)
{
	pid_t	pid;
	int		ret_code;

	if (is_no_abort(shell))
	{
		pid = _fork(shell);
		if (pid == 0)
		{
			close_secure(ast->closed_fd);
			forward_fds(ast);
			if (ast->write_fd && ast->write_fd[0] >= 0)
			{
				dup2(*ast->write_fd, STDOUT_FILENO);
				close(*ast->write_fd);
				*ast->write_fd = -2;
			}
			_execute_ast(shell, ast->cntl_op->left);
			close_fds(ast, CHILD);
			wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
			ret_code = shell->exit_code;
			(destroy_shell(shell), exit(ret_code));
		}
		else if (pid > 0)
		{
			close_secure(ast->write_fd);
			close_fds(ast, PARENT);
			if (ast->cntl_op->left)
				close_secure(ast->cntl_op->left->closed_fd);
			waitpid(pid, &shell->exit_code, 0);
		}
	}
}
