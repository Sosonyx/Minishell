/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/10/01 17:23:32 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static char	*next_sample(char **path)
{
	char	*ptr;

	while (*path && isasterisk(**path))
		(*path)++;
	ptr = *path;
	while (*ptr && !isasterisk(*ptr))
		ptr++;
	return (ft_substr(*path, 0, ptr - *path));
}

static char	*find_match(char *ptested, char *psample)
{
	if (psample && *psample)
		return (ft_strstr(ptested, psample));
	else
		return (ptested);
}

static char	*align_segment(char *segment, char *psample)
{
	int	n;

	if (!segment || !psample)
		return (segment);
	n = ft_strlen(psample);
	return (segment + n);
}

static int	_pathmatch(char *ptested, char *pref)
{
	char	*psample;

	while (1)
	{
		if (!*ptested && !*pref)
			return (1);
		else if (!iswildcard(pref))
			return (strncmprev(ptested, pref, ft_min(strlen(ptested), ft_strlen(pref))) == 0);
		else
		{
			psample = next_sample(&pref);
			if (!psample || !*psample)
				return (free(psample), 1);
			ptested = find_match(ptested, psample);
			if (!ptested)
				return (free(psample), 0);
			ptested = align_segment(ptested, psample);
			if (islastsequence(pref))
				while (*pref && isasterisk(*pref))
					pref++;
			else
				pref = align_segment(pref, psample);
			return (free(psample), _pathmatch(ptested, pref));
		}
	}
}

int	pathmatch(char *ptested, char *pref)
{
	struct s_pathmatch	wref;
	char				*ptr;

	if (iswildcard(pref))
	{
		if (ft_strncmp(ptested, DOT_ENTRY, 2) && ft_strncmp(ptested, DOTDOT_ENTRY, 2))
		{
			ptr = pref;
			if (*pref && *pref != '*')
			{
				while (*ptr && *ptr != '*')
					ptr++;
				wref.start_sequence = ft_substr(pref, 0, ptr - pref);
				if (ft_strncmp(ptested, wref.start_sequence, ft_strlen(wref.start_sequence)))
					return (free(wref.start_sequence), 0);
				else
					free(wref.start_sequence);
			}
			while (*ptr)
				ptr++;
			if (*--ptr != '*')
			{
				wref.end_sequence = ptr;
				while (*ptr && *ptr != '*')
					ptr--;
				wref.end_sequence = ft_substr(pref, ptr - pref + 1, wref.end_sequence - ptr + 1);
				if (strncmprev(ptested, wref.end_sequence, ft_strlen(wref.end_sequence)))
					return (free(wref.end_sequence), 0);
				else
					free(wref.end_sequence);
			}
		}
		else
			return (0);
	}
	return (_pathmatch(ptested, pref));
}
