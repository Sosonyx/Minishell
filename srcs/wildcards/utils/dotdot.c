/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dotdot.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:25:18 by fox               #+#    #+#             */
/*   Updated: 2025/09/26 11:47:32 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	isonlywildcard(char *field)
{
	if (!field)
	{
		return (0);
	}
	while (*field)
	{
		if (*field++ != '*')
			return (0);
	}
	return (1);
}

int	isdotdotdotentry(char *dir)
{
	if (!strcmp(DOT_ENTRY, dir) || !strcmp(DOTDOT_ENTRY, dir))
		return (1);
	else
		return (0);
}

int	skipdotdotdot(char *dir, char *field)
{
	if (isonlywildcard(field))
	{
		return (isdotdotdotentry(dir));
	}
	else if (!ft_strcmp(dir, DOTDOT_ENTRY) && !ft_strcmp(field, DOT_ENTRY))
	{
		return (1);
	}
	else if (!ft_strcmp(dir, DOT_ENTRY) && !ft_strcmp(field, DOTDOT_ENTRY))
	{
		return (1);
	}	
	else
		return (0);
}
