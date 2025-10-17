/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_abort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:30:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/17 14:05:47 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_abort(t_shell_p shell, char *errmsg)
{
	if (errmsg)
		print_generic_error(shell, errmsg);
	shell->abort = true;
	if (shell->exit_code != 130 && shell->exit_code != 131)
		shell->exit_code = ERRVAL1;
}
