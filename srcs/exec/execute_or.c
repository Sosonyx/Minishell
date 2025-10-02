/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/02 16:31:18 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_or(t_minishell_p shell, t_ast_p ast)
{
	forward_fds(ast);
	_execute_ast(shell, ast->cntl_op->left);
	wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
	if (NO_ABORT && shell->exit_code)
	{
		_execute_ast(shell, ast->cntl_op->right);
	}
	else if (NO_ABORT && !shell->exit_code && (ast->cntl_op->right->type == OP_AND))
	{
		_execute_ast(shell, ast->cntl_op->right->cntl_op->right);
	}
	wait_if_leaf(ast->cntl_op->right->leaf, &shell->exit_code);
}
