/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 17:44:12 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/15 15:25:34 by ihadj            ###   ########.fr       */
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

int	handle_cd_error(t_shell_p shell, int errnum, char *oldpwd)
{
	if (errnum == ENOTDIR)
		prt_err(shell, "cd", "Not a directory");
	else if (errnum == EACCES)
		prt_err(shell, "cd", "Permission denied");
	else
		prt_err(shell, "cd", strerror(errnum));
	free(oldpwd);
	return (ERRVAL1);
}
