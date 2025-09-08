/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messager.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:04:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/08 13:39:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_annouce(int fd, char *announce, char *separator)
{
	write(fd, announce, ft_strlen(announce));
	write(fd, separator, ft_strlen(separator));
}

static void self_announce(int fd)
{
	print_annouce(fd, SELF, COLUMN);
}

void speak(int fd, char *announce, char *separator, bool announce_self)
{
	if (announce_self)
		self_announce(fd);
	print_annouce(fd, announce, separator);
}
