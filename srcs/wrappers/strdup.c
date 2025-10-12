/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:34:46 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/12 13:39:24 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_strdup(t_shell_p shell, const char *s)
{
	char	*ptr;

	if (is_no_abort(shell))
	{
		ptr = ft_strdup(s);
		if (!ptr)
			set_abort(shell, MEM_ERRMSG);
		return (ptr);
	}
	else
		return (NULL);
}
