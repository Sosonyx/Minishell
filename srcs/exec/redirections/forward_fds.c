/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forward_fds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/14 14:49:17 by fox               #+#    #+#             */
/*   Updated: 2025/09/14 14:53:34 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	forward_fds(t_ast_p ast)
{
	t_ast_p	branch;
	
	branch = ast->cntl_op->left;
	if (branch)
	{
		branch->read_fd = ast->read_fd;
		branch->write_fd = ast->write_fd;
	}
	branch = ast->cntl_op->right;
	if (branch)
	{
		branch->read_fd = ast->read_fd;
		branch->write_fd = ast->write_fd;
	}
}
