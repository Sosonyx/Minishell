/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messager.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:04:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 14:06:50 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_annouce(int fd, char *announce, char *separator)
{
	write(fd, announce, ft_strlen(announce));
	write(fd, separator, ft_strlen(separator));
}

static void	self_announce(t_shell_p shell, int fd)
{
	print_annouce(fd, shell->name, COLUMN);
}

void	speak(t_shell_p shell, int fd, char *announce, char *separator)
{
	if (shell)
		self_announce(shell, fd);
	print_annouce(fd, announce, separator);
}

void	speak2(t_shell_p shell, int fd, char **announces)
{
	if (announces && *announces)
	{
		if (shell)
			self_announce(shell, fd);
		while (*announces && *(announces + 1))
			print_annouce(fd, *announces++, COLUMN);
		print_annouce(fd, *announces, NEWLINE);
	}
}
