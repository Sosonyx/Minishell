/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:34 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/14 15:37:02 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_and(t_minishell_p shell, t_ast_p ast)
{
	int	rstatus;

	forward_fds(ast);
	if (ast->cntl_op->left->leaf)
		preconfig_leaf(shell, ast->cntl_op->left->leaf);
	rstatus = execute_ast(shell, ast->cntl_op->left);
	if (!rstatus && ast->cntl_op->right)
	{		
		if (ast->cntl_op->right->leaf)
			preconfig_leaf(shell, ast->cntl_op->right->leaf);
		rstatus = execute_ast(shell, ast->cntl_op->right);
	}
	return (rstatus);
}
