/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:24:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 17:28:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_err(char *name)
{
	self_speak(STDERR_FILENO, name, COLUMN, true);
	self_speak(STDERR_FILENO, FILE_ERRMSG, NEWLINE, false);
}

void	print_file_error(char *filename)
{
	print_err(filename);
}

void	print_cmd_error(char *cmd_name)
{
	print_err(cmd_name);
}

void	print_generic_error(char *errmsg)
{
	write(STDERR_FILENO, errmsg, ft_strlen(errmsg));
}
