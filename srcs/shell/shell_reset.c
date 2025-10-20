/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:16:52 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/20 20:37:31 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_reset(t_shell_p shell)
{
	// int	n;

	if (!shell)
		return ;
	shell->ast_root = NULL;
	shell->is_root = 0;
	shell->abort = 0;
	shell->forked = 0;
	// n = 0;
	// while (n < 1024)
	// {
	// 	if (shell->closed_hd_fd[n] > 2)
	// 		close_secure(&shell->closed_hd_fd[n]);
	// 	n++;
	// }
	ft_bzero(shell->closed_hd_fd, 1024 * sizeof(int));
}
