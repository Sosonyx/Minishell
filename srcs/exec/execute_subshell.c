/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/26 19:23:22 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	pid_t			pid;
	
	forward_fds(ast);
	
	pid = fork();
	if (pid == 0)
	{
		shell->last_status = _execute_ast(shell, ast->cntl_op->left);
		wait_if_leaf(ast->cntl_op->left->leaf, &shell->last_status);
		exit(shell->last_status);
	}
	else if (pid > 0)
	{
		close_fds(ast, PARENT);
		waitpid(pid, &shell->last_status, 0);
	}
	else
	{
		print_generic_error(shell, FORK_ERRMSG);
	}
	return (shell->last_status);
}

