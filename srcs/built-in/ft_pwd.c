/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:20:18 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/07 16:23:14 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_getcwd(char **env)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (env && env[++i])
	{
		if (ft_strncmp(env[i], "PWD=", 4) == 0)
			return (&env[i][j + 4]);
	}
	return (NULL);
}

int	ft_pwd(void)
{
	char *cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}
