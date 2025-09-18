/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:41 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/17 13:25:38 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}


static char	*ft_getenv(char **env, char *name)
{
	int		i;
	size_t	len;

	len = ft_strlen(name);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

static char	*get_target_dir(t_minishell *shell, char **args)
{
	if (!args[1])
		return (ft_getenv(shell->environ, "HOME")); // si jai pas de destination je reviens au home
	return (args[1]);
}

static int	update_pwd(t_minishell *shell, char *oldpwd, char *newpwd)
{
	// ici je parcours shell->env, puis je "realloc" oldpwd et newpwd avec la bonne valeur
	return (0);
}

int	ft_cd(t_minishell *shell, char **args)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (1);
	path = get_target_dir(shell, args);
	if (!path || chdir(path) == -1)
	{
		print_cd_error(path);
		return (free(oldpwd), 1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (free(oldpwd), 1);
	update_pwd(shell, oldpwd, newpwd);
	return (0);
}
