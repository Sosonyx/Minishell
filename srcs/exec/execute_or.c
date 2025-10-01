/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/01 15:20:49 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_or(t_minishell_p shell, t_ast_p ast)
{
	forward_fds(ast);
	_execute_ast(shell, ast->cntl_op->left);
	wait_if_leaf(ast->cntl_op->left->leaf, &g_status);
	if (NO_ABORT && g_status)
	{
		_execute_ast(shell, ast->cntl_op->right);
	}
	else if (NO_ABORT && !g_status && (ast->cntl_op->right->type == OP_AND))
	{
		_execute_ast(shell, ast->cntl_op->right->cntl_op->right);
	}
	wait_if_leaf(ast->cntl_op->right->leaf, &g_status);
}
