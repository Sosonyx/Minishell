/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   catpath.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:27:15 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 13:27:24 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

char *catpath(char *pathopen, char *added)
{
	char	*new_path;
	char	*temp;
	
	new_path = ft_strjoin(pathopen, "/");
	if (new_path)
		temp = new_path;
	if (added)
	{
		new_path = ft_strjoin(new_path, added);
		free(temp);
	}
	return (new_path);
}
