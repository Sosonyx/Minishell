/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/16 17:24:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_or(t_minishell_p shell, t_ast_p ast)
{
	int	rstatus;

	forward_fds(ast);
	
	if (ast->cntl_op->left->leaf)
		preconfig_leaf(shell, ast->cntl_op->left->leaf);
	rstatus = _execute_ast(shell, ast->cntl_op->left);
	wait_if_leaf(ast->cntl_op->left->leaf, &rstatus);
	if (rstatus)
	{
		if (ast->cntl_op->right->leaf)
			preconfig_leaf(shell, ast->cntl_op->right->leaf);
		rstatus = _execute_ast(shell, ast->cntl_op->right);
	}
	else if (!rstatus && (ast->cntl_op->right->type == OP_AND))
	{
		if (ast->cntl_op->right->leaf)
			preconfig_leaf(shell, ast->cntl_op->right->leaf);
		rstatus = _execute_ast(shell, ast->cntl_op->right->cntl_op->right);
	}
	wait_if_leaf(ast->cntl_op->right->leaf, &rstatus);
	return (rstatus);
}
