/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_out.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:56:30 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 17:57:22 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_fd_out(t_ast_p ast)
{
	char *target;
	int fd_out;
	int prev = 0;

	while (ast->leaf->redir)
	{
		if (ast->leaf->redir->type == T_REDIR_OUT || ast->leaf->redir->type == T_APPEND)
			target = ast->leaf->redir->target;
		if (fd_out == T_REDIR_OUT)
		{
			fd_out = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out == -1)
			{
				print_file_error(target);
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
				print_file_error(target);
				close(prev);
				break;
			}
			else
			{
				close(prev);
				prev = fd_out;
			}
		}
		ast->leaf->redir = ast->leaf->redir->next;
		prev = fd_out;
	}
	return (fd_out);
}
