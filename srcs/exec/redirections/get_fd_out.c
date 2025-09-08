/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:56:30 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/08 15:57:58 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_fd_out(t_ast_p ast)
{
	char 		*target;
	int 		fd_out;
	int			prev = 0;
	t_redir_p	cur_redir;

	fd_out = STDOUT_FILENO;
	cur_redir = ast->leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_OUT || cur_redir->type == R_APPEND)
		{
			target = cur_redir->target;
			
			if (cur_redir->type == R_OUT)
			{
				fd_out = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
				if (fd_out == -1)
				{
					print_file_error(target, ENOENT);
					close(prev);
					break;
				}
				else
				{
					close(prev);
					prev = fd_out;
				}
			}
			else
			{
				fd_out = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
				if (fd_out == -1)
				{
					print_file_error(target, ENOENT);
					close(prev);
					break;
				}
				else
				{
					close(prev);
					prev = fd_out;
				}
			}
			prev = fd_out;
		}
		cur_redir = cur_redir->next;
	}
	return (fd_out);
}
