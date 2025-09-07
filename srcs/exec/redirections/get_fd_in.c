/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_fd_in.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:55:46 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 17:57:34 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int get_fd_in(t_ast_p ast)
{
	char *target;
	int fd_in;
	int prev;

	prev = 0;
	while (ast->leaf->redir)
	{
		if (ast->leaf->redir->type == T_REDIR_IN)
			target = ast->leaf->redir->target;
		fd_in = open(target, O_RDONLY);
		if (fd_in == -1)
		{
			print_file_error(target);
			close(prev);
			break;
		}
		else
		{
			close(prev);
			prev = fd_in;
		}
		ast->leaf->redir = ast->leaf->redir->next;
	}
	return (fd_in);
}
