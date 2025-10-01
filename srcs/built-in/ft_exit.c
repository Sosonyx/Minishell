/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:06 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/01 12:54:29 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_minishell_p shell, char **args)
{
	if (!args[1])
	{
		print_generic_error(NULL, "exit");
		exit(g_status);
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

// int	ft_exit(t_minishell_p shell, char **args)
// {
// 	long	code;

// 	if (!args[1])
// 	{
// 		print_generic_error(NULL, "exit");
// 		exit(g_status);
// 	}
// 	if (args[1] && args[2] && is_valid_number(args[1]))
// 	{
// 		print_generic_error(NULL, "exit");
// 		print_cmd_error2(shell, "exit", ARG_EXCESS_ERRMSG);
// 		exit(1);
// 	}
// 	if (args[2])
// 	{
// 		print_cmd_error2(shell, "exit", ARG_EXCESS_ERRMSG);
// 		return (1);
// 	}
// 	if (!is_valid_number(args[1]))
// 	{
// 		print_cmd_error2(shell, "exit", ARG_NON_NUM_ERRMSG);
// 		print_generic_error(NULL, "exit");
// 		exit(2);
// 	}
// 	code = ft_atol(args[1]);
// 	exit((unsigned char)code);
// }
