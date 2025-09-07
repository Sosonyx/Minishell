/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:37 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/07 14:08:47 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// la valeur de else est fixee arbitrairement
// probablement qu'il faudra pour minishell implementer les autres macros WIF*****(status)

int	get_exit_code(t_minishell_p shell)
{
	int	status;
	int	exit_code;
	int	last;

	exit_code = 0;
	last = shell->exec_var.cur_index - 1;
	if (last >= 0)
	{
		status = shell->exec_var.status_table[last];
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			exit_code = 128 + WTERMSIG(status); // convention unix, on dissocie 0-127 cas normal et 128+ cas d un signal
	}
	shell->exec_var.cur_index = 0;
	return (exit_code);
}

