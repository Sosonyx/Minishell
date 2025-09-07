/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:17:05 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/07 16:17:30 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	match_arg(char *entry, char *args)
{
	size_t	len;

	if (!entry || !args || !*args)
		return (0);
	len = ft_strlen(args);
	if (ft_strncmp(entry, args, len) != 0)
		return (0);
	if (entry[len] == '\0' || entry[len] == '=')
		return (1);
	return (0);
}

static int	should_remove(char *entry, char **args)
{
	int	i;

	i = 0;
	while (args && args[i])
	{
		if (match_arg(entry, args[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_unset(t_minishell *shell, char **args)
{
	int		i;
	int		j;
	int		len;
	char	**new_env;

	if (!args || !args[0])
		return (0);
	len = get_array_size(shell->environ);
	new_env = malloc(sizeof(char *) * (len + 1));
	if (!new_env)
		return (1);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (!should_remove(shell->environ[i], args))
			new_env[j++] = ft_strdup(shell->environ[i]);
		i++;
	}
	new_env[j] = NULL;
	free_array(shell->environ);
	shell->environ = new_env;
	return (0);
}
