/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:06 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/11 23:14:49 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_ft_exit(t_shell_p shell, int exit_code)
{
	destroy_shell(shell);
	exit(exit_code);
}

int	ft_exit(t_ast_p ast, t_shell_p shell, char **args)
{
	close_fds(ast, CHILD);
	restore_std_fileno(shell, ast);
	if (!args[1])
	{
		print_generic_error(NULL, "exit");
		_ft_exit(shell, shell->exit_code);
	}
	else if (args[1] && is_valid_number(args[1]))
	{
		if (args[2])
		{
			print_cmd_error2(shell, "exit", ARG_EXCESS_ERRMSG);
			return (ERRVAL1);
		}
		print_generic_error(NULL, "exit");
		_ft_exit(shell, ft_atoi(args[1]));
	}
	else
	{
		print_generic_error(NULL, "exit");
		print_cmd_error2(shell, "exit", ARG_NON_NUM_ERRMSG);
		_ft_exit(shell, 2);
	}
}
