/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:03 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/21 12:50:15 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_dup2(t_shell_p shell, int fd, int fd2)
{
	if (is_no_abort(shell))
	{
		if (fd > 2 && dup2(fd, fd2) == -1)
		{
			set_abort(shell, DUP2_ERRMSG);
			shell->exit_code = ERRVAL1;
			return (-1);
		}
		else
			return (close_secure(&fd), 0);
	}
	else
		return (-1);
}
