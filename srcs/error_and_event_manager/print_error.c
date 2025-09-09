/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:24:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 14:27:11 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#include "minishell.h"

static void	print_err(char *name, int err_num)
{
	speak(STDERR_FILENO, name, COLUMN, true);
	speak(STDERR_FILENO, strerror(err_num), NEWLINE, false);
}

void	print_file_error(char *filename, int err_num)
{
	print_err(filename, err_num);
}

void	print_cmd_error(char *cmd_name, int err_num)
{
	if (err_num == ENOENT)
	{
		speak(STDERR_FILENO, cmd_name, COLUMN, true);
		speak(STDERR_FILENO, CMD_ERRMSG, NEWLINE, false);
	}
	else
		print_err(cmd_name, err_num);
}

void	print_generic_error(char *errmsg)
{
	speak(STDERR_FILENO, errmsg, NEWLINE, true);
}
