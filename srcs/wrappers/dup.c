/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:19:41 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_dup(t_shell_p shell, int fd)
{
	int	dup_fd;

	if (is_no_abort(shell))
	{
		dup_fd = dup(fd);
		if (dup_fd == -1)
		{
			set_abort(shell, DUP_ERRMSG);
			shell->exit_code = ERRVAL1;
		}
		return (dup_fd);
	}
	return (-1);
}
