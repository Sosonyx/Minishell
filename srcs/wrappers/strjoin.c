/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:44:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 14:13:10 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*_strjoin(t_shell_p shell, char const *s1, char const *s2)
{
	char	*ptr;

	if (is_no_abort(shell))
	{
		ptr = ft_strjoin(s1, s2);
		if (!ptr)
			set_abort(shell, MEM_ERRMSG);
		return (ptr);
	}
	else
		return (NULL);
}
