/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:15 by fox               #+#    #+#             */
/*   Updated: 2025/09/30 20:52:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

char *catpath(char *pathopen, char *added)
{
	char	*new_path;
	char	*temp;
	
/* 	if (*pathopen == '/')
		new_path = ft_strdup(pathopen);
	else */
		new_path = ft_strjoin(pathopen, "/");
	if (new_path)
		temp = new_path;
	if (new_path && added)
	{
		new_path = ft_strjoin(new_path, added);
		free(temp);
	}
	return (new_path);
}
