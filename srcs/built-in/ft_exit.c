/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:06 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/02 16:31:18 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell_p shell, char **args)
{
	if (!args[1])
	{
		print_generic_error(NULL, "exit");
		exit(shell->exit_code);
	}
	else if (args[1] && is_valid_number(args[1]))
	{
		if (args[2])
		{
			print_cmd_error2(shell, "exit", ARG_EXCESS_ERRMSG);
			return (ERRVAL1);
		}
		print_generic_error(NULL, "exit");
		exit(ft_atoi(args[1]));
	}
	else
	{
		print_generic_error(NULL, "exit");
		print_cmd_error2(shell, "exit", ARG_NON_NUM_ERRMSG);
		exit(2);
	}
}
