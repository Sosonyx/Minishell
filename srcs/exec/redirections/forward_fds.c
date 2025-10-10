/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:17 by fox               #+#    #+#             */
/*   Updated: 2025/10/10 22:07:29 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forward_fds(t_ast_p ast)
{
	t_ast_p	branch;

	if (!ast || !ast->cntl_op)
		return ;
	branch = ast->cntl_op->left;
	if (branch)
	{
		branch->read_fd = ast->read_fd;
		branch->write_fd = ast->write_fd;
		branch->closed_fd = ast->closed_fd;
		branch->cur_pipe[0] = ast->cur_pipe[0];
		branch->cur_pipe[1] = ast->cur_pipe[1];
	}
	branch = ast->cntl_op->right;
	if (branch)
	{
		branch->read_fd = ast->read_fd;
		branch->write_fd = ast->write_fd;
		branch->closed_fd = ast->closed_fd;
		branch->cur_pipe[0] = ast->cur_pipe[0];
		branch->cur_pipe[1] = ast->cur_pipe[1];
	}
}
