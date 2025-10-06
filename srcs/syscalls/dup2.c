/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dup2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:11:03 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/06 15:32:41 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_dup2(t_minishell_p shell, int fd, int fd2)
{
	if (fd IS_VALID_FD && dup2(fd, fd2) == -1)
	{
		set_abort(shell, DUP2_ERRMSG);
		shell->exit_code = ERRVAL1;
		return (-1);
	}
	else
		return (0);
}
