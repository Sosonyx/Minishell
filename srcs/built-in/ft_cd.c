/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:41 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 17:48:02 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define DIR_ERRMSG		"error retrieving current directory"
#define PARDIR_ERRMSG	"cannot access parent directories"

static void	print_errmsg(t_shell_p shell, char **msg_parts)
{
	speak(shell, STDERR_FILENO, msg_parts[0], COLUMN);
	speak(NULL, STDERR_FILENO, msg_parts[1], COLUMN);
	speak(NULL, STDERR_FILENO, msg_parts[2], NOSEP);
	speak(NULL, STDERR_FILENO, msg_parts[3], NOSEP);
	speak(NULL, STDERR_FILENO, msg_parts[4], NEWLINE);
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

static char	*get_target_dir(t_shell *shell, char **args)
{
	if (!args[1])
		return (ft_getenv(shell->environ, "HOME"));
	return (args[1]);
}

static int	update_pwd(t_shell *shell, char *oldpwd, char *newpwd)
{
	int		i;
	char	*old_var;
	char	*new_var;

	old_var = _strjoin(shell, "OLDPWD=", oldpwd);
	new_var = _strjoin(shell, "PWD=", newpwd);
	if (!old_var || !new_var)
		return (free(old_var), free(new_var), 1);
	i = -1;
	while (shell->environ[++i])
	{
		if (!ft_strncmp(shell->environ[i], "OLDPWD=", 7))
		{
			free(shell->environ[i]);
			shell->environ[i] = _strdup(shell, old_var);
		}
		else if (!ft_strncmp(shell->environ[i], "PWD=", 4))
		{
			free(shell->environ[i]);
			shell->environ[i] = _strdup(shell, new_var);
		}
	}
	free(old_var);
	free(new_var);
	return (EXIT_SUCCESS);
}

int	ft_cd(t_shell_p shell, char **args)
{
	char	*path;
	char	*oldpwd;
	char	*newpwd;

	oldpwd = _getcwd(shell, &oldpwd);
	if (!oldpwd)
		oldpwd = _strdup(shell, ft_getenv(shell->environ, "PWD"));
	if (args[1] && args[2])
		return (prt_err(shell, "cd", ARG_EXCESS_ERRMSG), free(oldpwd), ERRVAL1);
	path = get_target_dir(shell, args);
	if (!path || chdir(path) == -1)
		return (prt_err(shell, "cd", strerror(ENOENT)), free(oldpwd), ERRVAL1);
	newpwd = _getcwd(shell, &newpwd);
	if (!newpwd)
	{
		print_errmsg(shell, (char *[]) \
		{"cd", DIR_ERRMSG, "getcwd", PARDIR_ERRMSG, strerror(ENOENT)});
		update_pwd(shell, oldpwd, path);
	}
	else
	{
		update_pwd(shell, oldpwd, newpwd);
		free(newpwd);
	}
	return (free(oldpwd), EXIT_SUCCESS);
}
