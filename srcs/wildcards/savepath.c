/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:22:28 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 19:58:01 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static char	*getfullpath(t_wildcard_p wc, struct dirent *sdir, char *path)
{
	if (wc && sdir && path)
	{
		path = catpath(path, sdir->d_name);
		if (wc->lastisdir)
			path = catpath(path, NULL);	
	}
	return (path);
}

void	savepath(t_wildcard_p wc, struct dirent *sdir, char *path, int depth)
{
	char	**ptr;
	char	*tmp;
	
	if (ishidden(sdir->d_name) || (sdir->d_type == DT_REG && wc->lastisdir) || skipdotdotdot(sdir->d_name, wc->spath[depth]))
		return ;
	if (pathmatch(sdir->d_name, wc->spath[depth]))
	{
		path = getfullpath(wc, sdir, path);
		if (!ishidden(path))
			addmatch(wc, path);
		else
			free(path);
	}
}
