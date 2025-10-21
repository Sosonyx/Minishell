/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:15:33 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/21 17:39:16 by ihadj            ###   ########.fr       */
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

static int	process_export_arg(t_shell_p shell, char **env, char *arg, int *j)
{
	int	env_index;

	if (!is_valid_var_name(arg))
	{
		printf("minishell: export: `%s': not a valid identifier\n", arg);
		return (-1);
	}
	env_index = find_var_index(env, arg);
	if (env_index >= 0)
	{
		free(env[env_index]);
		env[env_index] = _strdup(shell, arg);
	}
	else
	{
		env[*j] = _strdup(shell, arg);
		(*j)++;
	}
	return (1);
}

static int	add_or_replace_vars(t_shell_p shell, \
	char **env, char **args, int start_index)
{
	int	i;
	int	j;
	int	ret;

	i = -1;
	j = start_index;
	while (args[++i])
	{
		ret = process_export_arg(shell, env, args[i], &j);
		if (ret == -1)
			return (-1);
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
		return (ft_split_free(new_env), ERRVAL1);
	free_array(shell->environ);
	shell->environ = new_env;
	return (EXIT_SUCCESS);
}
