/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_or.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/12 16:14:08 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_or(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code;

	if (ast->prev_pipe)
	{
		ast->cntl_op->left->prev_pipe = ast->prev_pipe;
		ast->cntl_op->right->prev_pipe = ast->prev_pipe;
	}
	if (ast->cntl_op->left->leaf)
		preconfig_leaf(shell, ast->cntl_op->left->leaf);
	if (ast->cntl_op->right->leaf)
		preconfig_leaf(shell, ast->cntl_op->right->leaf);

	ret_code = execute_ast(shell, ast->cntl_op->left);
	if (ret_code)
	{
		ret_code = execute_ast(shell, ast->cntl_op->right);
	}
	else if (!ret_code && (ast->cntl_op->right->type == OP_AND || ast->cntl_op->right->type == OP_OR))
	{
		if (ast->prev_pipe)
			ast->cntl_op->right->cntl_op->right->prev_pipe = ast->prev_pipe;
		ret_code = execute_ast(shell, ast->cntl_op->right->cntl_op->right);
	}
	else if (!ret_code && ast->cntl_op->right->type == OP_PIPE)
	{
		ret_code = execute_ast(shell, ast->cntl_op->right);
	}
	return (ret_code);
}
