/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:16:52 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/21 13:55:30 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_reset(t_shell_p shell)
{
	if (!shell)
		return ;
	shell->ast_root = NULL;
	shell->is_root = 0;
	shell->abort = 0;
	shell->forked = 0;
	ft_bzero(shell->closed_fds, FD_MAX * sizeof(int));
	shell->n = 0;
}
