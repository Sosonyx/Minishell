/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:01:29 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/03 15:16:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_pipe(t_minishell_p shell, int *pipedes)
{
	if (!pipedes || pipe(pipedes) == -1)
	{
		set_abort(shell, PIP_ERRMSG);
		shell->exit_code = ERRVAL1;
		return (-1);
	}
	else
		return (0);
}
