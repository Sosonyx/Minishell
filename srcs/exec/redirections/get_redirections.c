/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:43:19 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/09 16:49:54 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_prev(int prev)
{
	if (prev > 2)
		close(prev);
}

void	get_fd_in_pipe(t_leaf_p leaf, int *fd_in, int pipe[2])
{
	char 		*target;
	int 		prev;
	t_redir_p	cur_redir;
	bool		has_redir_in;

	prev = 0;
	has_redir_in = false;
	cur_redir = leaf->redir;
	*fd_in = STDIN_FILENO;
	while (cur_redir)
	{
		if (cur_redir->type == R_IN)
		{
			has_redir_in = true;
			target = cur_redir->target;
			*fd_in = open(target, O_RDONLY);
			if (*fd_in == -1)
			{
				print_file_error(target, ENOENT);
				close_prev(prev);
				break ;
			}
			else
			{
				close_prev(prev);
				prev = *fd_in;
			}
		}
		cur_redir = cur_redir->next;
	}
	if (pipe && !has_redir_in)
	{
		*fd_in = pipe[0];
		
	}
}


static void	get_redir_in(t_leaf_p leaf, int *fd_in)
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

void	get_fd_out_pipe(t_leaf_p leaf, int *fd_out, int pipe[2])
{
	char 		*target;
	int			prev = 0;
	t_redir_p	cur_redir;
	int			open_flags;
	bool		has_redir_out;

	has_redir_out = 0;
	*fd_out = STDOUT_FILENO;
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		open_flags = get_open_flag(cur_redir->type);
		if (open_flags != -1)
		{
			has_redir_out = true;
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
	if (pipe && !has_redir_out)
	{
		*fd_out = pipe[1];
	}	
}

static void	get_redir_out(t_leaf_p leaf, int *fd_out)
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

void	get_redirections_pipe(t_leaf_p leaf, int fds[2], int pipefds[2])
{
    get_fd_in_pipe(leaf, &(leaf->fds[0]), pipefds);
    get_fd_out_pipe(leaf, &(leaf->fds[1]), pipefds);
}

void	get_redirections(t_leaf_p leaf, int fds[2])
{
    get_redir_in(leaf, &(leaf->fds[0]));
    get_redir_out(leaf, &(leaf->fds[1]));
}
