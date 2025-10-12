/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:57:35 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/12 13:40:12 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_valid_number(char *str)
{
	int	i;

	if (!str || !str[0])
		return (0);
	i = 0;
	if (str[i] == '+' || str[i] == '-')
		i++;
	if (!str[i] || !(str[i] >= '0' && str[i] <= '9'))
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i]))
			return (0);
		i++;
	}
	return (1);
}

long long	ft_atol(const char *nptr)
{
	int			i;
	long long	nb;
	int			sign;

	i = 0;
	nb = 0;
	sign = 1;
	while (((nptr[i] >= 9 && nptr[i] <= 13) || nptr[i] == ' '))
		i++;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		nb = nb * 10 + (nptr[i] - '0');
		if (nb < -9223372036854775807 || nb > 9223372036854775807)
			return (0);
		i++;
	}
	return ((sign * nb));
}

static void	dup_small_env(t_shell_p shell, char **new_env)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	new_env[0] = _strjoin(shell, "PWD=", pwd);
	new_env[1] = _strdup(shell, "SHLVL=1");
	new_env[2] = _strdup(shell, "_=/usr/bin/env");
}

char	**dup_env(t_shell_p shell, char **envp)
{
	char	**small_env;

	if (!envp || !envp[0])
	{
		small_env = _calloc(shell, 5, sizeof(char *));
		if (!small_env)
			print_generic_error(shell, MEM_ERRMSG);
		else
			dup_small_env(shell, small_env);
		return (small_env);
	}
	return (_split_clone(shell, envp));
}

int	get_array_size(char **arr)
{
	int	i;

	if (!arr)
		return (0);
	i = 0;
	while (arr[i])
		i++;
	return (i);
}
