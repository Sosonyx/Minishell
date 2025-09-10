/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/10 13:54:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static int	get_open_flag(t_redirtype redirtype)
{
	if (redirtype == R_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirtype == R_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

static void	get_redir_in(t_leaf_p leaf)
{
	char 		*target;
	int 		prev;
	t_redir_p	cur_redir;

	prev = 0;
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_IN)
		{
			target = cur_redir->target;
			leaf->fds[0] = open(target, O_RDONLY);
			if (leaf->fds[0] == -1)
			{
				print_file_error(target, ENOENT);
				close_prev(prev);
				break;
			}
			else
			{
				leaf->r_in = true;
				close_prev(prev);
				prev = leaf->fds[0];
			}
		}
		cur_redir = cur_redir->next;
	}
	if (!leaf->r_in)
		leaf->fds[0] = STDIN_FILENO;
}

static void	get_redir_out(t_leaf_p leaf)
{
	char 		*target;
	int			prev = 0;
	t_redir_p	cur_redir;
	int			open_flags;
	
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		open_flags = get_open_flag(cur_redir->type);
		if (open_flags != -1)
		{
			target = cur_redir->target;
			leaf->fds[1] = open(target, open_flags, 0644);
			if (leaf->fds[1] == -1)
			{
				print_file_error(target, ENOENT);
				close_prev(prev);
				break;
			}
			else
			{
				leaf->r_out = true;
				close_prev(prev);
				prev = leaf->fds[1];
			}
		}
		cur_redir = cur_redir->next;
	}
	if (!leaf->r_out)
		leaf->fds[1] = STDOUT_FILENO;
}

void	get_redirections(t_leaf_p leaf)
{
	get_redir_in(leaf);
	get_redir_out(leaf);
}
 */

////////////////////////////////////////////////////////////////////////////////////
/// 
/// 


static int	get_open_flag(t_redirtype redirtype)
{
	if (redirtype == R_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirtype == R_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

// open et dup2 a proteger

void	duplicate_fds(t_leaf_p leaf)
{
	int	open_flag;
	
	if (!leaf->r_in && leaf->pipefd[0] >= 0)
	{
		dup2(leaf->pipefd[0], STDIN_FILENO);
	}
	if (!leaf->r_out && leaf->pipefd[1] >= 0)
	{
		dup2(leaf->pipefd[1], STDOUT_FILENO);
	}
	if (leaf->r_in)	
	{
		leaf->fds[0] = open(leaf->r_in_path, O_RDONLY, 0644);
		dup2(leaf->fds[0], STDIN_FILENO);
	}
	if (leaf->r_out)
	{
		open_flag = get_open_flag(leaf->redir->type);
		leaf->fds[1] = open(leaf->r_out_path, open_flag, 0644);
		dup2(leaf->fds[1], STDOUT_FILENO);
	}			
}
