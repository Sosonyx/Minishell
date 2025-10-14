/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:44:12 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 17:44:22 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_old_env(t_shell_p shell, \
	char **new_env, char **old_env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_env[i] = _strdup(shell, old_env[i]);
		i++;
	}
}
