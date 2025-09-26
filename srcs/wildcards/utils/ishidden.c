/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ishidden.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:54:08 by fox               #+#    #+#             */
/*   Updated: 2025/09/26 12:02:44 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

bool	ishidden(char *dir)
{
	if (dir && *dir)
	{
		if (!ft_strncmp(dir, "./", 2))
			return (ishidden(dir + 2));
		else if (!ft_strncmp(dir, "../", 3))
			return (ishidden(dir + 3));
		else if (dir && *dir == '.')
			return (1);
		else
			return (0);
	}
	else
		return (0);
}
