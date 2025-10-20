/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_reset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:16:52 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/20 17:18:53 by ihadj            ###   ########.fr       */
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
}
