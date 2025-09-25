/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_leaf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/25 17:50:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_prev(int prev)
{
	if (prev IS_VALID_FD)
		close(prev);
}

static int	get_open_flag(t_redirtype redirtype)
{
	if (redirtype == R_IN)
		return (O_RDONLY);
	else if (redirtype == R_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirtype == R_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

static int	open_files(t_minishell_p shell, t_leaf_p leaf, t_redir_p cur_redir)
{
	int		open_flag;
	int		*target_fd;
	bool	*r_flag;
	int		errnum;

	if (cur_redir->type == R_IN)
	{
		target_fd = &leaf->fds[0];
		r_flag = &leaf->r_in;
	}
	else
	{
		target_fd = &leaf->fds[1];
		r_flag = &leaf->r_out;
	}
	open_flag = get_open_flag(cur_redir->type);
	*target_fd = open(cur_redir->target, open_flag, OPEN_PERM);
	errnum = errno;
	if (*target_fd == -1)
	{
		print_file_error(shell, cur_redir->target, errnum);
		leaf->abort = true;
	}
	else
	{
		*r_flag = true;
	}
	return (*target_fd);
}

static int	set_redir(t_minishell_p shell, t_leaf_p leaf)
{
	t_redir_p	cur_redir;
	int			prev_in;
	int			prev_out;
	
	prev_in = 0;
	prev_out = 0;
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type & (R_IN | R_OUT | R_APPEND))
		{
			if (open_files(shell, leaf, cur_redir) == -1)
			{
				close_prev(prev_in);
				close_prev(prev_out);
				return (-1);
			}
			else
			{
				if (cur_redir->type & R_IN)
				{
					close_prev(prev_in);
					prev_in = leaf->fds[0];
				}
				else if (cur_redir->type & (R_OUT | R_APPEND))
				{
					close_prev(prev_out);
					prev_out = leaf->fds[1];
				}
					
			}
		}
		cur_redir = cur_redir->next;
	}
	if (leaf->hd_fd[0] IS_VALID_FD)
	{
		close_secure(&leaf->fds[0]);
		leaf->fds[0] = leaf->hd_fd[0];
	}
	return (0);
}

int	redirect_leaf(t_minishell_p shell, t_ast_p ast)
{
	if (!ast->leaf->r_in && ast->read_fd && *ast->read_fd IS_VALID_FD)
	{
		dup2(*ast->read_fd, STDIN_FILENO);
	}
	if (!ast->leaf->r_out && ast->write_fd && *ast->write_fd IS_VALID_FD)
	{
		dup2(*ast->write_fd, STDOUT_FILENO);
	}		
	if (ast->leaf->r_in || ast->leaf->r_out)	
	{
		if (set_redir(shell, ast->leaf) == -1)
			return (-1);

		if (ast->leaf->fds[0] IS_VALID_FD)
			dup2(ast->leaf->fds[0], STDIN_FILENO);

		if (ast->leaf->fds[1] IS_VALID_FD)
			dup2(ast->leaf->fds[1], STDOUT_FILENO);
	}
	return (0);
}

// static void	close_prev(int prev)
// {
// 	if (prev IS_VALID_FD)
// 		close(prev);
// }

// static int	get_open_flag(t_redirtype redirtype)
// {
// 	if (redirtype == R_IN)
// 		return (O_RDONLY);
// 	else if (redirtype == R_OUT)
// 		return (O_WRONLY | O_CREAT | O_TRUNC);
// 	else if (redirtype == R_APPEND)
// 		return (O_WRONLY | O_CREAT | O_APPEND);
// 	else
// 		return (-1);
// }

// static int	open_files(t_minishell_p shell, t_leaf_p leaf, t_redir_p cur_redir, t_redirtype redirtype)
// {
// 	int		open_flag;
// 	int		*target_fd;
// 	bool	*r_flag;
// 	int		errnum;

// 	if (redirtype == R_IN)
// 	{
// 		target_fd = &leaf->fds[0];
// 		r_flag = &leaf->r_in;
// 	}
// 	else
// 	{
// 		target_fd = &leaf->fds[1];
// 		r_flag = &leaf->r_out;
// 	}
// 	open_flag = get_open_flag(cur_redir->type);
// 	*target_fd = open(cur_redir->target, open_flag, OPEN_PERM);
// 	errnum = errno;
// 	if (*target_fd == -1)
// 	{
// 		print_file_error(shell, cur_redir->target, errnum);
// 		leaf->abort = true;
// 	}
// 	else
// 	{
// 		*r_flag = true;
// 	}
// 	return (*target_fd);
// }

// static int	set_redir(t_minishell_p shell, t_leaf_p leaf, t_redirtype redirtype)
// {
// 	t_redir_p	cur_redir;
// 	int			prev_redir;
	
// 	prev_redir = 0;
// 	cur_redir = leaf->redir;
// 	while (cur_redir)
// 	{
// 		if (cur_redir->type & redirtype)
// 		{
// 			if (open_files(shell, leaf, cur_redir, redirtype) == -1)
// 			{
// 				close_prev(prev_redir);
// 				return (-1);
// 			}
// 			else
// 			{
// 				close_prev(prev_redir);
// 				if (redirtype == R_IN)
// 					prev_redir = leaf->fds[0];
// 				else
// 					prev_redir = leaf->fds[1];
// 			}
// 		}
// 		cur_redir = cur_redir->next;
// 	}
// 	if (leaf->hd_fd[0] IS_VALID_FD)
// 	{
// 		close_secure(&leaf->fds[0]);
// 		leaf->fds[0] = leaf->hd_fd[0];
// 	}
// 	return (0);
// }

// int	redirect_leaf(t_minishell_p shell, t_ast_p ast)
// {
// 	if (!ast->leaf->r_in && ast->read_fd && *ast->read_fd IS_VALID_FD)
// 	{
// 		dup2(*ast->read_fd, STDIN_FILENO);
// 	}
// 	if (!ast->leaf->r_out && ast->write_fd && *ast->write_fd IS_VALID_FD)
// 	{
// 		dup2(*ast->write_fd, STDOUT_FILENO);
// 	}		
// 	if (ast->leaf->r_in)	
// 	{
// 		if (set_redir(shell, ast->leaf, R_IN) == -1)
// 			return (-1);
// 		else
// 			dup2(ast->leaf->fds[0], STDIN_FILENO);
// 	}
// 	if (ast->leaf->r_out)
// 	{
// 		if (set_redir(shell, ast->leaf, R_OUT | R_APPEND))
// 			return (-1);
// 		else
// 			dup2(ast->leaf->fds[1], STDOUT_FILENO);
// 	}
// 	return (0);
// }

