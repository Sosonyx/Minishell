/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_abort.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 16:30:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/03 15:55:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_abort(t_minishell_p shell, char *errmsg)
{
	if (errmsg)
		print_generic_error(shell, errmsg);
	shell->abort = true;
}
