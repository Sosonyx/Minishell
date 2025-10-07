/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:20:18 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getcwd(char **env)
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

int	ft_pwd(t_shell_p shell, char **args)
{
	char	*cwd;

	(void)args;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		cwd = ft_getcwd(shell->environ);
		ft_putstr_fd(cwd, 1);
		ft_putstr_fd("\n", 1);
		return (EXIT_SUCCESS);
	}
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (EXIT_SUCCESS);
}
