/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/20 14:57:35 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/07 16:25:52 by ihadj            ###   ########.fr       */
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

char	**dup_env(char **envp)
{
    int		count;
    char	**copy;
    int		i;

    count = get_array_size(envp);
    copy = malloc(sizeof(char *) * (count + 1));
    if (!copy)
        return (NULL);
    i = 0;
    while (i < count)
    {
        copy[i] = ft_strdup(envp[i]);
        i++;
    }
    copy[i] = NULL;
    return (copy);
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
