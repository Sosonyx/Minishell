/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:34 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/12 16:14:08 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_and(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code = 0;

	ast->cntl_op->left->read_fd = ast->read_fd;
	ast->cntl_op->left->write_fd = ast->write_fd;
	ast->cntl_op->right->read_fd = ast->read_fd;
	ast->cntl_op->right->write_fd = ast->write_fd;

	if (ast->cntl_op->left->leaf)
		preconfig_leaf(shell, ast->cntl_op->left->leaf);
	if (ast->cntl_op->right->leaf)
		preconfig_leaf(shell, ast->cntl_op->right->leaf);

	ret_code = execute_ast(shell, ast->cntl_op->left);
	
	if (!ret_code && ast->cntl_op->right)
	{		
		ret_code = execute_ast(shell, ast->cntl_op->right);
	}
	return (ret_code);
}
