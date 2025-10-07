/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_abort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:30:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_abort(t_shell_p shell, char *errmsg)
{
	if (errmsg)
		print_generic_error(shell, errmsg);
	shell->abort = true;
	shell->exit_code = ERRVAL1;
}
