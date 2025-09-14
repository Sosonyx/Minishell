/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:38:16 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/11 12:38:21 by cgajean          ###   ########.fr       */
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
	}
	if (mode)
	{
		if (ast->cur_pipe)
		{
			close_secure(&ast->cur_pipe[0]);
			close_secure(&ast->cur_pipe[1]);
		}
		close_secure(ast->write_fd);
		close_secure(ast->read_fd);
	}
}

void	close_lfds(int fds[2])
{
	if (fds)
	{
		close_secure(&fds[0]);
		close_secure(&fds[1]);
	}
}


