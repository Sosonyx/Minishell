/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_clone.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:50:22 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 14:13:37 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**_split_clone(t_shell_p shell, char **strs)
{
	char	**new_strs;

	if (is_no_abort(shell))
	{
		new_strs = ft_split_clone(strs);
		if (!new_strs)
			set_abort(shell, MEM_ERRMSG);
		return (new_strs);
	}
	else
		return (NULL);
}
