/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:24:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:17:11 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static void	print_err(t_minishell_p shell, char *name, int err_num)
{
	speak(shell, STDERR_FILENO, name, COLUMN);
	speak(NULL, STDERR_FILENO, strerror(err_num), NEWLINE);
}

void	print_file_error(t_minishell_p shell, char *filename, int err_num)
{
	print_err(shell, filename, err_num);
}

void	print_cmd_error(t_minishell_p shell, char *cmd_name, int err_num)
{
	if (err_num == ENOENT)
	{
		speak(shell, STDERR_FILENO, cmd_name, COLUMN);
		speak(NULL, STDERR_FILENO, CMD_ERRMSG, NEWLINE);
	}
	else
		print_err(shell, cmd_name, err_num);
}

void	print_generic_error(t_minishell_p shell, char *errmsg)
{
	speak(shell, STDERR_FILENO, errmsg, NEWLINE);
}
