/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:15:33 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/08 12:40:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_var_name(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	if (!ft_isalpha(str[0]) && str[0] != '_')
		return (0);
	i = 1;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

static int	find_var_index(char **env, char *arg)
{
	int	i;
	int	len;

	if (!env || !arg)
		return (-1);
	len = 0;
	while (arg[len] && arg[len] != '=')
		len++;
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], arg, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

static void	copy_old_env(t_shell_p shell, char **new_env, char **old_env, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		new_env[i] = _strdup(shell, old_env[i]);
		i++;
	}
}

static int	add_or_replace_vars(t_shell_p shell, char **env, char **args, int start_index)
{
	int	i;
	int	j;
	int	env_index;

	i = -1;
	j = start_index;
	while (args[++i])
	{
		if (is_valid_var_name(args[i]))
		{
			env_index = find_var_index(env, args[i]);
			if (env_index >= 0)
			{
				free(env[env_index]);
				env[env_index] = _strdup(shell, args[i]);
			}
			else
			{
				env[j] = _strdup(shell, args[i]);
				j++;
			}
		}
		else
		{
			printf("minishell: export: `%s': not a valid identifier\n", args[i]);	//	/!\ printf interdit
			return (-1);
		}
	}
	env[j] = NULL;
	return (1);
}

int	ft_export(t_shell_p shell, char **args_to_add)
{
	char	**new_env;
	int		env_count;
	int		add_count;

	if (!args_to_add || !args_to_add[0])
		return (EXIT_SUCCESS);
	env_count = get_array_size(shell->environ);
	add_count = get_array_size(args_to_add);
	new_env = _calloc(shell, (env_count + add_count + 1), sizeof(char *));
	if (!new_env)
		return (ERRVAL1);
	copy_old_env(shell, new_env, shell->environ, env_count);
	if ((add_or_replace_vars(shell, new_env, args_to_add, env_count)) == -1)
		return (ERRVAL1);
	free_array(shell->environ);
	shell->environ = new_env;
	return (EXIT_SUCCESS);
}
