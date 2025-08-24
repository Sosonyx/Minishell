/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built-in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/19 14:52:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/24 14:43:12 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char **env, const char *name)
{
	int		i;
	size_t	len;

	len = strlen(name);
	i = 0;
	while (env[i])
	{
		if (strncmp(env[i], name, len) == 0 && env[i][len] == '=')
			return (env[i] + len + 1);
		i++;
	}
	return (NULL);
}

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

static void	reorder_env(char ***envp, int start)
{
	char	**env;
	int		i;

	env = *envp;
	if (!envp || !env || start < 0 || !env[start])
		return ;
	free(env[start]);
	i = start;
	while (env[i])
	{
		env[i] = env[i + 1];
		i++;
	}
}

void	ft_unset(char ***envp, char **value)
{
	char	**env;
	int		i;
	int		j;
	int		len;

	i = -1;
	j = -1;
	env = *envp;
	while (env && env[++i])
	{
		j = 0;
		len = ft_strlen(value[j]);
		while (value[++j])
		{
			if (ft_strncmp(env[i], value[j], len) == 0 && env[i][len] == '=')
			{
				free(env[i]);
				reorder_env(envp, i);
			}
		}
	}
}

int	ft_cd(char *newpwd, char **env)
{
	char	*cwd;

	cwd = ft_getcwd(env);
	if (!newpwd)
		chdir("/home");
	chdir(newpwd);
	printf("PWD = %s\n", cwd);
	return (1);
}

void	ft_env(char **env)
{
	int	i;

	i = -1;
	while (env[++i])
		printf("%s\n", env[i]);
}

void	ft_echo(char *str, int option)
{
	if (option)
		printf("%s", str);
	else
		printf("%s\n", str);
}

// int	ft_exit(char **option, t_ms	exit_code)
// {
//     int	flag;

//     flag = 0;
//     if (!option || !option[0] || !option[0][0])
//         exit(exit_code.previous_exitcode);
//     if (option[1])
//         flag = 1;
//     if (is_valid_number(option[0]) && !flag)
//         exit((unsigned char)ft_atol(option[0]));
//     else if (is_valid_number(option[0]) && flag)
//     {
//         ft_putstr_fd("minishell: exit: ", 2);
//         ft_putstr_fd(option[0], 2);
//         ft_putstr_fd(": too many arguments\n", 2);
//         return (1);
//     }
//     else if (!is_valid_number(option[0]))
//     {
//         ft_putstr_fd("minishell: exit: ", 2);
//         ft_putstr_fd(option[0], 2);
//         ft_putstr_fd(": numeric argument required\n", 2);
//         exit(2);
//     }
//     return (0);
// }

static char	**ft_export(char **env, char **args_to_add)
{
	char	**new_env;
	int		count;
	int		env_count;
	int		i;

	count = 0;
	env_count = 0;
	if (!args_to_add)
		return (NULL);
	while (args_to_add[count])
		count++;
	while (env[env_count])
		env_count++;
	new_env = malloc(sizeof(char *) * (env_count + count + 1));
	if (!new_env)
		return (NULL);
	i = -1;
	while (++i < env_count)
		new_env[i] = ft_strdup(env[i]); // attention a la protection du strdup
	count = -1;
	while (args_to_add[++count])
		new_env[env_count + count] = strdup(args_to_add[count]); // attention a la protection du strdup
	new_env[env_count + count] = NULL;
	return (new_env);
}
