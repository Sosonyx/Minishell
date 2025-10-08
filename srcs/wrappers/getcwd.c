/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getcwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/08 12:16:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/08 12:59:28 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_getcwd(t_shell_p shell, char **buf)
{
	if (is_no_abort(shell))
	{
		*buf = getcwd(NULL, 0);
		if (errno == ENOMEM)
			set_abort(shell, MEM_ERRMSG);
		return (*buf);
	}
	else
		return (NULL);
}
