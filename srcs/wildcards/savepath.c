/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:22:28 by fox               #+#    #+#             */
/*   Updated: 2025/09/30 19:21:35 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static char	*getfullpath(t_wildcard_p wc, struct dirent *sdir, char *path)
{
	char	*tmp;
	
	if (wc && sdir && path)
	{
		path = catpath(path, sdir->d_name);
		if (wc->lastisdir)
		{
			tmp = path;
			path = catpath(path, NULL);
			free(tmp);
		}
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
		free(path);
	}
}
