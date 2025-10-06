/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:12:03 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/06 14:12:19 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	open_files(t_minishell_p shell, t_leaf_p leaf, t_redir_p cur_redir)
{
	int		open_flag;
	int		*target_fd;
	bool	*r_flag;

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
	if (*target_fd == -1)
	{
		print_file_error(shell, cur_redir->target, errno);
		leaf->abort = true;
	}
	else
		*r_flag = true;
	return (*target_fd);
}
