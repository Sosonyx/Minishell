/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ishidden.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:54:08 by fox               #+#    #+#             */
/*   Updated: 2025/10/21 17:14:34 by ihadj            ###   ########.fr       */
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
