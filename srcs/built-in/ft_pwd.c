/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:20:18 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/24 17:46:19 by fox              ###   ########.fr       */
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

int	ft_pwd(t_minishell_p shell, char **args)
{
	char	*cwd;

	(void)args;
	if (args && args[1])
	{
		print_cmd_error2(shell, "pwd", ARG_EXCESS_ERRMSG);
		return (ERRVAL2);
	}
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (ERRVAL2);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	free(cwd);
	return (EXIT_SUCCESS);
}
