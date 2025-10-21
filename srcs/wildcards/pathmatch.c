/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/10/21 17:16:15 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	_compare(char c1, char c2)
{
	return (c1 - c2);
}

int	pathmatch(char *ptested, char *pref, int state)
{
	if (ptested && pref && !*ptested && !*pref)
		return (1);
	if ((*pref == '\'' && state != 2) || (*pref == '"' && state != 1))
		state = quote_state(state, *pref++);
	if (!isasterisk(*pref) || state)
	{
		if (!*ptested || !*pref || _compare(*ptested, *pref))
			return (0);
		else
			return (pathmatch(ptested + 1, pref + 1, state));
	}
	while (pref && isasterisk(*pref) && !state)
	{
		pref++;
		if (!*pref)
			return (1);
	}
	while (ptested && *ptested)
		if (pathmatch(ptested++, pref, state))
			return (1);
	return (0);
}
