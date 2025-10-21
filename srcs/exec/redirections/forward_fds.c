/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:17 by fox               #+#    #+#             */
/*   Updated: 2025/10/21 13:55:30 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forward_fds(t_ast_p ast)
{
	if (!ast || !ast->cntl_op)
		return ;
	// close_hd_fds(ast->cntl_op->left, ast);
	// if (ast->closed_fds[0] > 2)
	// {
	// 	ft_memcpy(ast->cntl_op->left->closed_fds, ast->closed_fds, FD_MAX * sizeof(int));
	// 	ft_memcpy(ast->cntl_op->right->closed_fds, ast->closed_fds, FD_MAX * sizeof(int));
	// }
	if (ast->cntl_op->left)
	{
		ast->cntl_op->left->read_fd = ast->read_fd;
		ast->cntl_op->left->write_fd = ast->write_fd;
		ast->cntl_op->left->closed_fd = ast->closed_fd;
	}
	if (ast->cntl_op->right)
	{
		ast->cntl_op->right->read_fd = ast->read_fd;
		ast->cntl_op->right->write_fd = ast->write_fd;
		ast->cntl_op->right->closed_fd = ast->closed_fd;
	}
}
