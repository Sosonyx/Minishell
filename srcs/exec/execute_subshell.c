/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/16 19:46:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	int				rstatus;
	pid_t			pid;

	rstatus = 0;
	ast->subpid = fork();
	if (ast->subpid == 0)
	{
		forward_fds(ast);
			
		rstatus = _execute_ast(shell, ast->cntl_op->left);
		exit(rstatus);
	}
	else if (ast->subpid > 0)
	{
		close_fds(ast, PARENT);
		waitpid(ast->subpid, &rstatus, 0);
		wait_if_leaf(ast->cntl_op->left->leaf, &rstatus);
	}
	else
	{
		print_generic_error(FORK_ERRMSG);
	}
	return (rstatus);
}

