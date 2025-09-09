/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:24:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 09:54:33 by cgajean          ###   ########.fr       */
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
	print_err(cmd_name, err_num);
}

void	print_generic_error(char *errmsg)
{
	speak(STDERR_FILENO, errmsg, NEWLINE, true);
}
