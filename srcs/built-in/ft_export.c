/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:15:33 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/17 14:17:03 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export(t_minishell *shell, char **args_to_add)
{
	char	**new_env;
	int		env_count;
	int		add_count;
	int		i;
	int		j;

	if (!args_to_add || !args_to_add[0])
		return (0);
	env_count = get_array_size(shell->environ);
	add_count = get_array_size(args_to_add);
	new_env = malloc(sizeof(char *) * (env_count + add_count + 1));
	if (!new_env)
		return (1);
	i = -1;
	while (++i < env_count)
		new_env[i] = ft_strdup(shell->environ[i]);
	j = -1;
	while (++j < add_count)
		new_env[env_count + j] = ft_strdup(args_to_add[j]);
	new_env[env_count + add_count] = NULL;
	free_array(shell->environ);
	shell->environ = new_env;
	return (0);
}
