/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredocs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:30:25 by fox               #+#    #+#             */
/*   Updated: 2025/09/17 16:40:54 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_input_heredocs(t_leaf_p leaf, t_redir_p redir)
{
	char		*hd;
	
	pipe(leaf->hd_fd);
	while (1)
	{
		hd = readline(">");
		if (!hd)
			continue ;
		if (*hd == 4)
		{
			free(hd);
		}
		else if (ft_strcmp(hd, redir->limiter))
		{
			write(leaf->hd_fd[1], hd, ft_strlen(hd));
			write(leaf->hd_fd[1], "\n", 1);
			free(hd);
		}
		else
			break;
	}
	close_secure(&leaf->hd_fd[1]);	
}

void	input_heredocs(t_leaf_p leaf)
{
	t_redir_p	redir;
	
	redir = leaf->redir;
	while (redir)
	{
		if (redir->type & (R_IN | R_HDOC))
			close_secure(&leaf->hd_fd[0]);
		if (redir->type == R_HDOC)
		{
			_input_heredocs(leaf, redir);
		}
		redir = redir->next;
	}
}
