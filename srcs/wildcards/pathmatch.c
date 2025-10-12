/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/10/12 13:35:22 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	_compare(char c1, char c2)
{
	return (c1 - c2);
}

int	pathmatch(char *ptested, char *pref, int state)
{
	if (!*ptested && !*pref)
		return (1);
	if ((*pref == '\'' && state != 2) || (*pref == '"' && state != 1))
		state = quote_state(state, *pref++);
	if (!isasterisk(*pref) || state)
	{
		if (_compare(*ptested, *pref))
			return (0);
		else
			return (pathmatch(ptested + 1, pref + 1, state));
	}
	while (isasterisk(*pref) && !state)
	{
		pref++;
		if (!*pref)
			return (1);
	}
	while (*ptested)
		if (pathmatch(ptested++, pref, state))
			return (1);
	return (0);
}
