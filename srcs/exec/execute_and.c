/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:34 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/02 16:31:18 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_and(t_minishell_p shell, t_ast_p ast)
{
	forward_fds(ast);
	_execute_ast(shell, ast->cntl_op->left);
	wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
	if (NO_ABORT && !shell->exit_code && ast->cntl_op->right)
	{		
		_execute_ast(shell, ast->cntl_op->right);
		wait_if_leaf(ast->cntl_op->right->leaf, &shell->exit_code);
	}
}
