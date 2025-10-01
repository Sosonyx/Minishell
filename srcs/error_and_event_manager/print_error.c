/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:24:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/01 15:24:41 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_err(t_minishell_p shell, char *name, int errnum)
{
	speak(shell, STDERR_FILENO, name, COLUMN);
	speak(NULL, STDERR_FILENO, strerror(errnum), NEWLINE);
}

void	print_file_error(t_minishell_p shell, char *filename, int errnum)
{
	print_err(shell, filename, errnum);
}

// void	print_cmd_error(t_minishell_p shell, char *cmd_name, int errnum)
// {
// 	if (errnum == 42)
// 	{
// 		speak(shell, STDERR_FILENO, cmd_name, COLUMN);
// 		speak(NULL, STDERR_FILENO, FILE_ERRMSG, NEWLINE);
// 	}
// 	else if (errnum == ENOENT)
// 	{
// 		speak(shell, STDERR_FILENO, cmd_name, COLUMN);
// 		speak(NULL, STDERR_FILENO, CMD_ERRMSG, NEWLINE);
// 	}
// 	else
// 		print_err(shell, cmd_name, errnum);
// }

void	print_cmd_error(t_minishell_p shell, char *cmd_name, int errnum)
{
	if (errnum == ENOENT && !ft_strchr(cmd_name, '/'))
	{
		speak(shell, STDERR_FILENO, cmd_name, COLUMN),
		speak(NULL, STDERR_FILENO, CMD_ERRMSG, NEWLINE);
	}
	else
		print_err(shell, cmd_name, errnum);
}

void	print_cmd_error2(t_minishell_p shell, char *cmd_name, char *errmsg)
{
	speak(shell, STDERR_FILENO, cmd_name, COLUMN);
	speak(NULL, STDERR_FILENO, errmsg, NEWLINE);
}

void	print_generic_error(t_minishell_p shell, char *errmsg)
{
	speak(shell, STDERR_FILENO, errmsg, NEWLINE);
}
