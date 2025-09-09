/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 11:30:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_array(char **array)
{
	int	i;

	if (!array)
		return ;
	i = 0;
	while (array[i])
	{
		free(array[i]);
		i++;
	}
	free(array);
}

static int	get_paths_index(char **env)
{
	int		i;
	char	*path;

	i = 0;
	path = "PATH=";
	while (env && env[i])
	{
		if (ft_strncmp(env[i], path, 5) == 0)
			return (i);
		i++;
	}
	return (-1);
}

static char	*get_correct_path(char **array, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	path = NULL;
	tmp = ft_strjoin("/", cmd);
	if (!tmp)
		return (NULL);
	while (array[i])
	{
		path = ft_strjoin(array[i], tmp);
		if (!path)
			return (free(tmp), NULL);
		if (access(path, X_OK) == 0)
			return (free(tmp), path);
		free(path);
		i++;
	}
	free(tmp);
	return (ft_strdup(cmd));
}

char	*find_cmd(char *cmd, char **env)
{
	int		paths_index;
	char	**paths;
	char	*correct_path;

	if (!cmd)
		return (NULL);
	if (ft_strchr(cmd, '/'))
	{
		if (access(cmd, F_OK) == 0 && access(cmd, X_OK) == 0)
			return (ft_strdup(cmd));
		return (ft_strdup(cmd));
	}
	paths_index = get_paths_index(env);
	if (paths_index == -1)
		return (ft_strdup(cmd));
	paths = ft_split(env[paths_index] + 5, ':');
	if (!paths)
		return (ft_strdup(cmd));
	correct_path = get_correct_path(paths, cmd);
	free_array(paths);
	return (correct_path);
}

