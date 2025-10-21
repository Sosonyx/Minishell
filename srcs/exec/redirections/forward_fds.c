/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:17 by fox               #+#    #+#             */
/*   Updated: 2025/10/21 15:08:58 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
