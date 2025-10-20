/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:16:06 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/20 17:27:01 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_ft_exit(t_shell_p shell, int exit_code)
{
	destroy_shell(shell);
	exit(exit_code);
}

static void	_prt_err(t_shell_p shell, char *errmsg)
{
	if (shell && shell->forked == false)
		prt_err(shell, "exit", errmsg);
}

/* static void	print_non_num_error(t_shell_p shell, char *arg)
{
	if (shell && shell->forked == false)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(": numeric argument required\n", STDERR_FILENO);
} */

static void	print_non_num_error(t_shell_p shell, char *arg, char *errmsg)
{
	if (shell && shell->forked == false)
		ft_putstr_fd("exit\n", STDERR_FILENO);
	ft_putstr_fd("minishell: exit: ", STDERR_FILENO);
	if (arg)
		ft_putstr_fd(arg, STDERR_FILENO);
	ft_putstr_fd(errmsg, STDERR_FILENO);
}

int	ft_exit(t_ast_p ast, t_shell_p shell, char **args)
{
	close_fds(ast, CHILD);
	restore_std_fileno(shell, ast);
	if (!args[1])
	{
		if (shell->forked == false)
			print_generic_error(NULL, "exit");
		_ft_exit(shell, shell->exit_code >> 8);
	}
	else if (args[1] && is_valid_number(args[1]))
	{
		if (args[2])
		{
			print_non_num_error(shell, NULL, ARG_EXCESS_ERRMSG);
			return (ERRVAL1);
		}
		if (shell && shell->forked == false)
			print_generic_error(NULL, "exit");
		_ft_exit(shell, ft_atoi(args[1]));
	}
	else
	{
		print_non_num_error(shell, args[1], ": numeric argument required\n");
		_ft_exit(shell, 2);
	}
	return (0);
}
