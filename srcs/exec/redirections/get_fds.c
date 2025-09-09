/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fds.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:43:19 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/09 11:44:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_prev(int prev)
{
	if (prev > 2)
		close(prev);
}

static void	get_fd_in(t_leaf_p leaf, int *fd_in)
{
	char 		*target;
	int 		prev;
	t_redir_p	cur_redir;

	prev = 0;
	cur_redir = leaf->redir;
	*fd_in = STDIN_FILENO;
	while (cur_redir)
	{
		if (cur_redir->type == R_IN)
		{
			target = cur_redir->target;
			*fd_in = open(target, O_RDONLY);
			if (*fd_in == -1)
			{
				print_file_error(target, ENOENT);
				close_prev(prev);
				break;
			}
			else
			{
				close_prev(prev);
				prev = *fd_in;
			}
		}
		cur_redir = cur_redir->next;
	}
}

static int	get_open_flag(t_redirtype redirtype)
{
	if (redirtype == R_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirtype == R_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

static void	get_fd_out(t_leaf_p leaf, int *fd_out)
{
	char 		*target;
	int			prev = 0;
	t_redir_p	cur_redir;
	int			open_flags;
	
	*fd_out = STDOUT_FILENO;
	cur_redir = leaf->redir;	
	
	while (cur_redir)
	{
		open_flags = get_open_flag(cur_redir->type);
		if (open_flags != -1)
		{
			target = cur_redir->target;
			*fd_out = open(target, open_flags, 0644);
			if (*fd_out == -1)
			{
				print_file_error(target, ENOENT);
				close_prev(prev);
				break;
			}
			else
			{
				close_prev(prev);
				prev = *fd_out;
			}
		}
		cur_redir = cur_redir->next;
	}
}

void	get_fds(t_leaf_p leaf)
{
	get_fd_in(leaf, &leaf->fds[0]);
	get_fd_out(leaf, &leaf->fds[1]);
}
