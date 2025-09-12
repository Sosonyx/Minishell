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
		close_secure(&ast->leaf->pipefd[0]);
		close_secure(&ast->leaf->pipefd[1]);
	}
	if (mode)
	{
		close_secure(&ast->cur_pipe[0]);
		close_secure(&ast->cur_pipe[1]);
		if (ast->prev_pipe)
		{
			close_secure(&ast->prev_pipe[0]);
			close_secure(&ast->prev_pipe[1]);
		}
		if (ast->leaf && ast->leaf->cur_pipe)
		{
			close_secure(&ast->leaf->cur_pipe[0]);
			close_secure(&ast->leaf->cur_pipe[1]);
		}
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

