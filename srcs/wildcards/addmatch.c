/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addmatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:32:58 by fox               #+#    #+#             */
/*   Updated: 2025/10/06 15:28:07 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	matchlist_resize(t_wildcard_p wc)
{
	char	**ptr;

	if (!wc->tmp_matches)
	{
		wc->tmp_matches = ft_calloc(++wc->tmp_totalmatches + 1, sizeof(char *));
	}
	else
	{
		ptr = ft_realloc(wc->tmp_matches, (wc->tmp_totalmatches) * sizeof(char *), (++wc->tmp_totalmatches + 1) * sizeof(char *));
		if (ptr)
			wc->tmp_matches = ptr;
	}					
}

void	addmatch(t_wildcard_p wc, char *path)
{
	if (path)
	{
		matchlist_resize(wc);
		if (wc->startbydot && !strncmp(path, "./", 2))
			wc->tmp_matches[wc->tmp_totalmatches - 1] = ft_strdup(path + 2);
		else if (!strncmp(path, "//", 2))
		{
			if (wc->isstartdir)
				wc->tmp_matches[wc->tmp_totalmatches - 1] = ft_strdup(path + 1);
			else
				wc->tmp_matches[wc->tmp_totalmatches - 1] = ft_strdup(path + 2);
		}
		else
			wc->tmp_matches[wc->tmp_totalmatches - 1] = ft_strdup(path);
	}
}
