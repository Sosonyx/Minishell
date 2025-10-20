/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:17 by fox               #+#    #+#             */
/*   Updated: 2025/10/20 19:52:15 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forward_fds(t_ast_p ast)
{
	if (!ast || !ast->cntl_op)
		return ;
	// close_hd_fds(ast->cntl_op->left, ast);
	// if (ast->closed_hd_fd[0] > 2)
	// {
	// 	ft_memcpy(ast->cntl_op->left->closed_hd_fd, ast->closed_hd_fd, 1024 * sizeof(int));
	// 	ft_memcpy(ast->cntl_op->right->closed_hd_fd, ast->closed_hd_fd, 1024 * sizeof(int));
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
