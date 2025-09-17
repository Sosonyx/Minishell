/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:22:31 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	int				rstatus;
	pid_t			pid;
	
	pid = fork();
	if (pid == 0)
	{
		forward_fds(ast);

		rstatus = _execute_ast(shell, ast->cntl_op->left);
		wait_if_leaf(ast->cntl_op->left->leaf, &rstatus);
		exit(rstatus);
	}
	else if (pid > 0)
	{
		close_fds(ast, PARENT);
		waitpid(pid, &rstatus, 0);
	}
	else
	{
		print_generic_error(shell, FORK_ERRMSG);
	}
	return (rstatus);
}

