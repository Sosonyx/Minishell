/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:52 by fox               #+#    #+#             */
/*   Updated: 2025/10/13 16:30:58 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	_recdir(t_shell_p shell, t_wildcard_p wc, char *pathopen, int depth)
{
	char	*path;

	path = NULL;
	if (!skipdotdotdot(wc->sdir->d_name, wc->spath[depth]) \
		&& !ishidden(wc->sdir->d_name) && pathmatch(wc->sdir->d_name, \
		wc->spath[depth], 0))
	{
		path = catpath(shell, pathopen, wc->sdir->d_name);
		recdir(shell, wc, path, depth + 1);
		free(path);
	}
}

void	recdir(t_shell_p shell, t_wildcard_p wc, char *pathopen, int depth)
{
	DIR				*dirp;

	dirp = NULL;
	if (is_no_abort(shell))
	{
		if (pathopen)
			dirp = opendir(pathopen);
		if (dirp)
		{
			wc->sdir = readdir(dirp);
			while (is_no_abort(shell) && wc->sdir)
			{
				if (depth < wc->max_depth && wc->sdir->d_type == DT_DIR)
				{
					_recdir(shell, wc, pathopen, depth);
				}
				else if (depth == wc->max_depth)
				{
					savepath(shell, wc, pathopen, depth);
				}
				wc->sdir = readdir(dirp);
			}
			closedir(dirp);
		}
	}
}
