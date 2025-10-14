/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hd_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:20:38 by fox               #+#    #+#             */
/*   Updated: 2025/10/14 14:06:41 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_errmsg(t_shell_p shell, char (*msg_parts)[36], char *limiter)
{
	(void) ft_strcpy(msg_parts[0], "warning: here-document at line");
	(void) ft_itoa_static(msg_parts[1], shell->readlines);
	(void) ft_strcpy(msg_parts[2], "delimited by end-of-file (wanted `");
	(void) ft_strcpy(msg_parts[3], limiter);
	(void) ft_strcpy(msg_parts[4], "')");
}

static void	print_errmsg(t_shell_p shell, char (*msg_parts)[36])
{
	speak(shell, STDERR_FILENO, msg_parts[0], COLUMN);
	speak(NULL, STDERR_FILENO, msg_parts[1], COLUMN);
	speak(NULL, STDERR_FILENO, msg_parts[2], NOSEP);
	speak(NULL, STDERR_FILENO, msg_parts[3], NOSEP);
	speak(NULL, STDERR_FILENO, msg_parts[4], NEWLINE);
}

void	print_hd_error(t_shell_p shell, char *limiter)
{
	char	errmsg[5][36];

	ft_memset(errmsg, 0, 5 * 36 * sizeof(char));
	get_errmsg(shell, errmsg, limiter);
	print_errmsg(shell, errmsg);
}
