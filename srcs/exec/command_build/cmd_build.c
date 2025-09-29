/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 18:42:54 by ihadj            ###   ########.fr       */
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
		if (access(path, F_OK) == 0)
			return (free(tmp), path);
		free(path);
		i++;
	}
	free(tmp);
	return (NULL);
}

char	*find_cmd(t_minishell_p shell, t_ast_p ast)
{
	int		paths_index;
	char	**paths;

	if (!*ast->leaf->cmds)
		return (NULL);
	ast->leaf->exec_path = *ast->leaf->cmds;
	if (ft_strchr(*ast->leaf->cmds, '/'))
		return (ft_strdup(*ast->leaf->cmds));
	paths_index = get_paths_index(shell->environ);
	if (paths_index == -1)
		return (ft_strdup(*ast->leaf->cmds));
	paths = ft_split(shell->environ[paths_index] + 5, ':');
	if (!paths)
		return (ft_strdup(*ast->leaf->cmds));
	ast->leaf->exec_path = get_correct_path(paths, *ast->leaf->cmds);
	free_array(paths);
	return (ast->leaf->cmds[0]);
}
