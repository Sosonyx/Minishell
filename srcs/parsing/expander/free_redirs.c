/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 15:30:35 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/21 15:30:42 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir_p list)
{
	t_redir_p	tmp;

	while (list)
	{
		tmp = list->next;
		free(list->target);
		free(list->limiter);
		free(list);
		list = tmp;
	}
}
