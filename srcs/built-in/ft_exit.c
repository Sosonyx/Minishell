/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:06 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/07 16:16:14 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(char **args, int last_status)
{
	long	code;

	if (!args[1])
		exit(last_status);
	if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (1);
	}
	if (!is_valid_number(args[1]))
	{
		ft_putstr_fd("minishell: exit: numeric argument required\n", 2);
		ft_putstr_fd("exit\n", 2);
		exit(2);
	}
	code = ft_atol(args[1]);
	exit((unsigned char)code);
}
