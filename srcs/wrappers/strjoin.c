/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strjoin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:44:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/06 14:54:12 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


char	*_strjoin(t_minishell_p shell, char const *s1, char const *s2)
{
	char	*ptr;

	ptr = ft_strjoin(s1, s2);
	if (!ptr)
		set_abort(shell, MEM_ERRMSG);
	return (ptr);
}
