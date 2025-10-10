/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:06 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/10 19:50:12 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit(t_ast_p ast, t_shell_p shell, char **args)
{
	close_fds(ast, CHILD);
	restore_std_fileno(shell, ast);
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
