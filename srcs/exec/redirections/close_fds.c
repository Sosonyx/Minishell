/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 12:38:16 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/22 15:43:18 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_herited_fds(t_shell_p shell, t_ast_p ast)
{
	int	n;

	if (!ast)
		return ;
	n = 0;
	while (ast->leaf && n < FD_MAX && shell->closed_fds[n] != 0)
	{									
		if (shell->closed_fds[n] != ast->leaf->hd_fd[0] \
			&& shell->closed_fds[n] != ast->leaf->fds[0] \
			&& shell->closed_fds[n] != ast->leaf->fds[1])
			close_secure(&shell->closed_fds[n]);
		n++;
	}
}

void	close_fds(t_shell_p shell, t_ast_p ast, int mode)
{
	if (!ast)
		return ;
	if (ast->leaf)
	{
		close_secure(&ast->leaf->fds[0]);
		close_secure(&ast->leaf->fds[1]);
		close_secure(&ast->leaf->hd_fd[0]);
		close_secure(&ast->leaf->hd_fd[1]);
	}
	if (mode == CHILD)
	{
		close_secure(ast->write_fd);
		close_secure(ast->read_fd);
		close_secure(ast->closed_fd);
		close_herited_fds(shell, ast);
	}
}
