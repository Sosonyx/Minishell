/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:52:36 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/11 23:24:33 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	_fork(t_shell_p shell)
{
	pid_t	pid;

	if (is_no_abort(shell))
	{
		pid = fork();
		if (pid < 0)
		{
			set_abort(shell, FORK_ERRMSG);
			shell->exit_code = ERRVAL1;
		}
		return (shell->forked = true, pid);
	}
	return (-1);
}
