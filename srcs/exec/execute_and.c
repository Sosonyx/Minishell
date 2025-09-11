/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:34 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/11 15:34:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_and(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code = 0;

	if (ast->cntl_op->left->leaf)
		configure_leaf(shell, ast->cntl_op->left->leaf);
	if (ast->cntl_op->right->leaf)
		configure_leaf(shell, ast->cntl_op->right->leaf);

/* 	if (ast->prev_pipefds)
	{
		ast->cntl_op->left->prev_pipefds = ast->prev_pipefds;
		ast->cntl_op->right->prev_pipefds = ast->prev_pipefds;	
	} */
	// if (ast->cntl_op->left)
	// {
		ret_code = execute_ast(shell, ast->cntl_op->left);
	// }
	
	if (!ret_code && ast->cntl_op->right)
	{		
		ret_code = execute_ast(shell, ast->cntl_op->right);
	}
	return (ret_code);
}
