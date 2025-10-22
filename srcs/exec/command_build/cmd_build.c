/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_build.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:30:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/22 17:04:24 by ihadj            ###   ########.fr       */
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

static char	*get_correct_path(t_shell_p shell, char **paths, char *cmd)
{
	int		i;
	char	*tmp;
	char	*path;

	i = 0;
	if (cmd && !*cmd)
		return (NULL);
	tmp = _strjoin(shell, "/", cmd);
	if (!tmp)
		return (NULL);
	while (paths[i])
	{
		if (paths[i][0] == '\0')
			path = _strjoin(shell, "./", tmp + 1);
		else
			path = _strjoin(shell, paths[i], tmp);
		if (!path)
			return (free(tmp), NULL);
		if (access(path, F_OK | X_OK) == 0)
			return (free(tmp), path);
		free(path);
		i++;
	}
	free(tmp);
	return (NULL);
}

char	*cmd_build(t_shell_p shell, t_ast_p ast)
{
	int		paths_index;
	char	**paths;

	paths = NULL;
	if (!ast->leaf->cmds || !*ast->leaf->cmds)
		return (NULL);
	ast->leaf->exec_path = _strdup(shell, *ast->leaf->cmds);
	if (ft_strchr(*ast->leaf->cmds, '/'))
		return (_strdup(shell, *ast->leaf->cmds));
	paths_index = get_paths_index(shell->environ);
	paths = ft_split_path(shell, shell->environ, paths_index, ':');
	if (!paths)
		return (_strdup(shell, *ast->leaf->cmds));
	free(ast->leaf->exec_path);
	ast->leaf->exec_path = get_correct_path(shell, paths, *ast->leaf->cmds);
	free_array(paths);
	return (_strdup(shell, ast->leaf->cmds[0]));
}
