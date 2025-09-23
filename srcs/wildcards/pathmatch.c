/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 15:00:24 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

char *next_sample(char **path)
{
	char *ptr;

	while (*path && isasterisk(**path))
		(*path)++;

	ptr = *path;

	while (*ptr && !isasterisk(*ptr))
		ptr++;

	return (ft_substr(*path, 0, ptr - *path));
}

char *find_match(char *ptested, char *psample)
{
	if (psample && *psample)
		return (strstr(ptested, psample));
	else
		return (ptested);
}

char *align_segment(char *segment, char *psample)
{
	int n;

	if (!segment || !psample)
		return (segment);

	n = strlen(psample);
	return (segment + n);
}

int pathmatch(char *ptested, char *pref)
{
	char 		*psample;

	while (1)
	{
		if (!*ptested && !*pref)
			return (1);
		else if (!iswildcard(pref))
		{
			return (strncmprev(ptested, pref, ft_min(strlen(ptested), strlen(pref))));
		}
		else
		{
			psample = next_sample(&pref);
			if (!psample || !*psample)
			{
				return (free(psample), 1);
			}
			ptested = find_match(ptested, psample);
			if (!ptested)
				return (free(psample), 0);
			ptested = align_segment(ptested, psample);
			pref = align_segment(pref, psample);
			return (free(psample), pathmatch(ptested, pref));
		}
	}
}
