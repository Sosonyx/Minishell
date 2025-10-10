/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/10 14:10:52 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_or(t_shell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		forward_fds(ast);
		_execute_ast(shell, ast->cntl_op->left);
		wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
	}
	if (is_no_abort(shell))
	{
		if (shell->exit_code)
		{
			_execute_ast(shell, ast->cntl_op->right);
		}
		else if (!shell->exit_code && (ast->cntl_op->right->type == OP_AND))
		{
			_execute_ast(shell, ast->cntl_op->right->cntl_op->right);
			close_secure(ast->read_fd);
			// close_fds(ast, CHILD);
		}
		wait_if_leaf(ast->cntl_op->right->leaf, &shell->exit_code);
	}
}
