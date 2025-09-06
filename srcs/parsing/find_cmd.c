// #include "minishell.h"

// void	init_path(t_pipex *pipex)
// {
// 	char	*path;
// 	int		i;

// 	i = get_paths_index(pipex->env);
// 	if (i == -1)
// 	{
// 		ft_printf("Error: PATH not found in environment.\n");
// 		pipex->env_paths = NULL;
// 		return ;
// 	}
// 	path = pipex->env[i];
// 	pipex->env_paths = ft_split(path + 5, ':');
// }

// char	**get_cmd(char **av, int index)
// {
// 	char	**cmd;

// 	cmd = ft_split(av[index], ' ');
// 	if (!cmd)
// 		return (NULL);
// 	return (cmd);
// }

// void	init_args(t_pipex *pipex)
// {
// 	int		i;
// 	int		j;

// 	i = 0;
// 	j = 2;
// 	pipex->cmd_args = malloc(sizeof(char **) * (pipex->ac + 1));
// 	if (!pipex->cmd_args)
// 		return ;
// 	while (i < pipex->ac - 1)
// 	{
// 		pipex->cmd_args[i] = get_cmd(pipex->av, j++);
// 		if (!pipex->cmd_args[i++])
// 			return ;
// 	}
// 	pipex->cmd_args[i] = NULL;
// }

// void	get_all_paths(t_pipex *pipex)
// {
// 	int		i;
// 	int		j;
// 	char	**tmp;

// 	i = 0;
// 	j = 2;
// 	pipex->cmd_paths = malloc(sizeof(char *) * (pipex->ac - 2));
// 	if (!pipex->cmd_paths)
// 		return ;
// 	while (i < pipex->ac - 3)
// 	{
// 		tmp = get_cmd(pipex->av, j++);
// 		pipex->cmd_paths[i] = get_correct_path(pipex->env_paths, tmp[0]);
// 		if (!pipex->cmd_paths[i])
// 		{
// 			free_array(tmp);
// 			free_array(pipex->cmd_paths);
// 			pipex->cmd_paths = NULL;
// 			ft_printf("command not found\n");
// 			return ;
// 		}
// 		free_array(tmp);
// 		i++;
// 	}
// 	pipex->cmd_paths[i] = NULL;
// }

// int	get_paths_index(char **env)
// {
// 	int		i;
// 	char	*path;

// 	i = 0;
// 	path = "PATH=";
// 	while (env && env[i])
// 	{
// 		if (ft_strncmp(env[i], path, 5) == 0)
// 			return (i);
// 		i++;
// 	}
// 	return (-1);
// }

// char	*get_correct_path(char **array, char *cmd)
// {
// 	int		i;
// 	char	*tmp;
// 	char	*path;

// 	i = 0;
// 	path = NULL;
// 	tmp = ft_strjoin("/", cmd);
// 	if (!tmp)
// 		return (NULL);
// 	while (array[i])
// 	{
// 		path = ft_strjoin(array[i], tmp);
// 		if (!path)
// 			return (NULL);
// 		if (access(path, X_OK) == 0)
// 			return (free(tmp), path);
// 		i++;
// 		free(path);
// 	}
// 	return (free(tmp), strdup(cmd));
// }
// char	*find_cmd(char *cmd, char **env)
// {
//     int		paths_index;
//     char	**paths;
//     char	*correct_path;

//     if (access(cmd, X_OK) == 0)
//         return (strdup(cmd));
//     paths_index = get_paths_index(env);
//     if (paths_index == -1)
//         return (strdup(cmd));
//     paths = ft_split(env[paths_index] + 5, ':');
//     if (!paths)
//         return (strdup(cmd));
//     correct_path = get_correct_path(paths, cmd);
//     free_array(paths);
//     return (correct_path);
// }
