/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:55:46 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/08 15:09:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_fd_in(t_ast_p ast)
{
	char 		*target;
	int 		fd_in;
	int 		prev;
	t_redir_p	cur_redir;

	prev = 0;
	cur_redir = ast->leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_IN)
		{
			target = cur_redir->target;
			fd_in = open(target, O_RDONLY);
			if (fd_in == -1)
			{
				print_file_error(target, ENOENT);
				close(prev);
				break;
			}
			else
			{
				close(prev);
				prev = fd_in;
			}
		}
		cur_redir = cur_redir->next;
	}
	return (fd_in);
}
