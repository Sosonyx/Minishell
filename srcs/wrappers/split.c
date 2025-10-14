/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:22 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 14:13:33 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**_split(t_shell_p shell, const char *s, const char c)
{
	char	**str;

	if (is_no_abort(shell))
	{
		str = ft_split(s, c);
		if (!str)
			set_abort(shell, MEM_ERRMSG);
		return (str);
	}
	else
		return (NULL);
}
