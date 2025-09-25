/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:41 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/25 13:44:09 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* static void	print_cd_error(char *path)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(path, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
} */

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
	int		i;
	char	*old_var;
	char	*new_var;

	old_var = ft_strjoin("OLDPWD=", oldpwd);
	new_var = ft_strjoin("PWD=", newpwd);
	if (!old_var || !new_var)
		return (free(old_var), free(new_var), 1);
	i = 0;
	while (shell->environ[i])
	{
		if (!ft_strncmp(shell->environ[i], "OLDPWD=", 7))
		{
			free(shell->environ[i]);
			shell->environ[i] = ft_strdup(old_var);
		}
		else if (!ft_strncmp(shell->environ[i], "PWD=", 4))
		{
			free(shell->environ[i]);
			shell->environ[i] = ft_strdup(new_var);
		}
		i++;
	}
	free(old_var);
	free(new_var);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_minishell_p shell, char **args)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = getcwd(NULL, 0);
	if (!oldpwd)
		return (ERRVAL1);
	if (args[1] && args[2])
	{
		print_cmd_error2(shell, "cd", ARG_EXCESS_ERRMSG);
		return (free(oldpwd), ERRVAL1);
	}
	path = get_target_dir(shell, args);
	if (!path || chdir(path) == -1)
	{
		print_cmd_error2(shell, "cd", strerror(ENOENT));
		return (free(oldpwd), ERRVAL1);
	}
	newpwd = getcwd(NULL, 0);
	if (!newpwd)
		return (free(oldpwd), ERRVAL1);
	update_pwd(shell, oldpwd, newpwd);
	free(oldpwd);
	free(newpwd);
	return (EXIT_SUCCESS);
}
