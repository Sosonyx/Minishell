/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:34 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 14:16:48 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_and(t_minishell_p shell, t_ast_p ast)
{
	int	rstatus;

	forward_fds(ast);
	if (ast->cntl_op->left->leaf)
		preconfig_leaf(shell, ast->cntl_op->left->leaf);
	rstatus = _execute_ast(shell, ast->cntl_op->left);
	wait_if_leaf(ast->cntl_op->left->leaf, &rstatus);
	if (!rstatus && ast->cntl_op->right)
	{		
		if (ast->cntl_op->right->leaf)
			preconfig_leaf(shell, ast->cntl_op->right->leaf);
		rstatus = _execute_ast(shell, ast->cntl_op->right);
		wait_if_leaf(ast->cntl_op->right->leaf, &rstatus);
	}
	return (rstatus);
}
