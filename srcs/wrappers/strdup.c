/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strdup.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:34:46 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/08 12:33:17 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_strdup(t_shell_p shell, const char *s)
{
	size_t	size;
	char	*ptr;

	if (is_no_abort(shell))
	{
		size = ft_strlen(s);
		ptr = ft_strdup(s);
		if (!ptr)
			set_abort(shell, MEM_ERRMSG);
		return (ptr);
	}
	else
		return (NULL);
}
