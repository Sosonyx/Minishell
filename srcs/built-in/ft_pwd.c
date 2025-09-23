/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:20:18 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/17 13:36:19 by ihadj            ###   ########.fr       */
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

int	ft_pwd(char **args)
{
	char	*cwd;

	(void)args;
	// if (args && args[1])
	// {
	// 	ft_putstr_fd("minishell: pwd: too many arguments\n", 2);
	// 	return (ERRVAL2);
	// }
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERRVAL2);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (0);
}
