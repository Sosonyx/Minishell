/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:17 by fox               #+#    #+#             */
/*   Updated: 2025/10/11 19:37:42 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	forward_fds(t_ast_p ast)
// {
// 	t_ast_p	branch;

// 	if (!ast || !ast->cntl_op)
// 		return ;
// 	branch = ast->cntl_op->left;
// 	if (branch)
// 	{
// 		branch->read_fd = ast->read_fd;
// 		branch->write_fd = ast->write_fd;
// 		branch->closed_fd = ast->closed_fd;
// 	}
// 	branch = ast->cntl_op->right;
// 	if (branch)
// 	{
// 		branch->read_fd = ast->read_fd;
// 		branch->write_fd = ast->write_fd;
// 		branch->closed_fd = ast->closed_fd;
// 	}
// }

void	forward_fds(t_ast_p ast)
{
	if (!ast || !ast->cntl_op)
		return ;
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
