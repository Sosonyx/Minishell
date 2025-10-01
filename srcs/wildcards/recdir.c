/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:52 by fox               #+#    #+#             */
/*   Updated: 2025/10/01 15:37:15 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	_recdir(t_wildcard_p wc, struct dirent *sdir, char *pathopen, int depth)
{
	char	*path = NULL;

	if (!skipdotdotdot(sdir->d_name, wc->spath[depth]) && !ishidden(sdir->d_name) && pathmatch(sdir->d_name, wc->spath[depth]))
	{
		path = catpath(pathopen, sdir->d_name);
		recdir(wc, path, depth + 1);
		free(path);
	}
}

void	recdir(t_wildcard_p wc, char *pathopen, int depth)
{
	DIR				*dirp;
	struct dirent	*sdir;

	if (pathopen)
		dirp = opendir(pathopen);
	if (dirp)
	{
		sdir = readdir(dirp);
		while (sdir)
		{
			if (depth < wc->max_depth && sdir->d_type == DT_DIR)
			{
				_recdir(wc, sdir, pathopen, depth);
			}
			else if (depth == wc->max_depth)
			{
				savepath(wc, sdir, pathopen, depth);
			}
			sdir = readdir(dirp);
		}
		closedir(dirp);
	}
}
