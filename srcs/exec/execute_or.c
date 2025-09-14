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
	int	return_code;

	ast->cntl_op->left->read_fd = ast->read_fd;
	ast->cntl_op->left->write_fd = ast->write_fd;
	ast->cntl_op->right->read_fd = ast->read_fd;
	ast->cntl_op->right->write_fd = ast->write_fd;
	
	if (ast->cntl_op->left->leaf)
		preconfig_leaf(shell, ast->cntl_op->left->leaf);

	return_code = execute_ast(shell, ast->cntl_op->left);
	if (return_code)
	{
		if (ast->cntl_op->right->leaf)
			preconfig_leaf(shell, ast->cntl_op->right->leaf);
		return_code = execute_ast(shell, ast->cntl_op->right);
	}
	else if (!return_code && (ast->cntl_op->right->type == OP_AND))
	{
		if (ast->cntl_op->right->leaf)
			preconfig_leaf(shell, ast->cntl_op->right->leaf);
		return_code = execute_ast(shell, ast->cntl_op->right->cntl_op->right);
	}
	return (return_code);
}
