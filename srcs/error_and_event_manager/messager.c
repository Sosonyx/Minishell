/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messager.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:04:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/24 17:39:03 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_annouce(int fd, char *announce, char *separator)
{
	write(fd, announce, ft_strlen(announce));
	write(fd, separator, ft_strlen(separator));
}

static void self_announce(t_minishell_p shell, int fd)
{
	print_annouce(fd, shell->name, COLUMN);
}

void speak(t_minishell_p shell, int fd, char *announce, char *separator)
{
	if (shell)
		self_announce(shell, fd);
	print_annouce(fd, announce, separator);
}
