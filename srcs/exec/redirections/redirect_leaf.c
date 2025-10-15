/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_leaf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/15 22:57:22 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	overwrite_if_hd(t_shell_p shell, t_leaf_p leaf)
{
	(void)shell;
	if (leaf->hd_fd[0] > 2)
	{
		close_secure(&leaf->fds[0]);
		leaf->fds[0] = leaf->hd_fd[0];
	}
}

static void	write_fd(t_leaf_p leaf, t_redir_p redir, int *prev_fds)
{
	if (redir->type & (R_IN))
	{
		close_secure(&prev_fds[0]);
		prev_fds[0] = leaf->fds[0];
	}
	else if (redir->type & (R_OUT | R_APPEND))
	{
		close_secure(&prev_fds[1]);
		prev_fds[1] = leaf->fds[1];
	}
}

static int	set_redir(t_shell_p shell, t_leaf_p leaf)
{
	t_redir_p	cur_redir;
	int			prev_fds[2];

	ft_memset(prev_fds, 0, 2 * sizeof(int));
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type & (R_IN | R_OUT | R_APPEND))
		{
			if (open_files(shell, leaf, cur_redir) == -1)
			{
				close_secure(&leaf->fds[0]);
				close_secure(&leaf->fds[1]);
				return (-1);
			}
			else
				write_fd(leaf, cur_redir, prev_fds);
		}
		cur_redir = cur_redir->next;
	}
	overwrite_if_hd(shell, leaf);
	return (0);
}

int	redirect_leaf(t_shell_p shell, t_ast_p ast)
{
	int	retval;

	if (ast->leaf->abort)
		return (-1);
	else
	{
		retval = 0;
		if (!ast->leaf->r_in && ast->read_fd && *ast->read_fd > 2)
			retval = _dup2(shell, *ast->read_fd, STDIN_FILENO);
		if (!ast->leaf->r_out && ast->write_fd && *ast->write_fd > 2)
			retval = _dup2(shell, *ast->write_fd, STDOUT_FILENO);
		if ((ast->leaf->r_in || ast->leaf->r_out))
		{
			retval = set_redir(shell, ast->leaf);
			if (ast->leaf->fds[0] > 2)
			{
				retval = _dup2(shell, ast->leaf->fds[0], STDIN_FILENO);
			}
			if (ast->leaf->fds[1] > 2)
			{
				retval = _dup2(shell, ast->leaf->fds[1], STDOUT_FILENO);
			}
		}
		return (retval);
	}
}
