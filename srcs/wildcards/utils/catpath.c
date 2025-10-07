/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:15 by fox               #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

char	*catpath(t_shell_p shell, char *pathopen, char *added)
{
	char	*new_path;
	char	*temp;

	new_path = _strjoin(shell, pathopen, "/");
	if (is_no_abort(shell))
	{
		temp = new_path;
		new_path = _strjoin(shell, new_path, added);
	}
	return (new_path);
}
