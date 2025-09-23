/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addmatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:32:58 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 19:30:05 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	matchlist_resize(t_wildcard_p wc)
{
	char	**ptr;
	
	if (!wc->matches)
	{
		wc->matches = calloc(++wc->totalmatches + 1, sizeof(char *));
	}
	else
	{
		ptr = ft_realloc((void **) wc->matches, (wc->totalmatches + 1) * sizeof(char *), (++wc->totalmatches + 1) * sizeof(char *));
		if (ptr)
			wc->matches = ptr;
	}					
}

void	addmatch(t_wildcard_p wc, char *path)
{
	if (path)
	{
		matchlist_resize(wc);
		if (wc->startbydot && !strncmp(path, "./", 2))
			wc->matches[wc->totalmatches - 1] = strdup(path + 2);
		else
			wc->matches[wc->totalmatches - 1] = strdup(path);
	}
}
