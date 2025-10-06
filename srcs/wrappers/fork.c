/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 14:52:36 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/03 15:16:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

pid_t	_fork(t_minishell_p shell)
{
	pid_t	pid;

	pid = fork();
	if(pid < 0)
	{
		set_abort(shell, FORK_ERRMSG);
		shell->exit_code = ERRVAL1;
	}
	return (pid);
}
