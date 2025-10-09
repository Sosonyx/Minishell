/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:38:16 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/09 14:47:22 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_ast_p ast, int mode)
{
	if (!ast)
		return ;
	if (ast->leaf)
	{
		close_secure(&ast->leaf->fds[0]);
		close_secure(&ast->leaf->fds[1]);
		close_secure(&ast->leaf->hd_fd[0]);
		close_secure(&ast->leaf->hd_fd[1]);
	}
	if (mode == CHILD)
	{
		if (ast->cur_pipe)
		{
			close_secure(&ast->cur_pipe[0]);
			close_secure(&ast->cur_pipe[1]);
		}
		close_secure(ast->write_fd);
		close_secure(ast->read_fd);
		close_secure(ast->closed_fd);
	}
}
