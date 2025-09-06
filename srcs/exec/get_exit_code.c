/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_exit_code.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:13:37 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 18:18:30 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// la valeur de else est fixee arbitrairement
// probablement qu'il faudra pour minishell implementer les autres macros WIF*****(status)

int	get_exit_code(t_minishell_p shell)
{
	int	status;

	status = shell->exec_var.status_table[shell->exec_var.cur_index];
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	else
	{
		return (0);
	}
}
