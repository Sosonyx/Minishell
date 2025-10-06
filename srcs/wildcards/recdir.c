/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:52 by fox               #+#    #+#             */
/*   Updated: 2025/10/06 15:50:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	_recdir(t_minishell_p shell, t_wildcard_p wc, struct dirent *sdir, char *pathopen, int depth)
{
	char	*path = NULL;

	if (!skipdotdotdot(sdir->d_name, wc->spath[depth]) && !ishidden(sdir->d_name) && pathmatch(sdir->d_name, wc->spath[depth]))
	{
		path = catpath(shell, pathopen, sdir->d_name);
		recdir(shell, wc, path, depth + 1);
		free(path);
	}
}

void	recdir(t_minishell_p shell, t_wildcard_p wc, char *pathopen, int depth)
{
	DIR				*dirp;
	struct dirent	*sdir;

	if (is_no_abort(shell))
	{
		if (pathopen)
			dirp = opendir(pathopen);
		if (dirp)
		{
			sdir = readdir(dirp);
			while (is_no_abort(shell) && sdir)
			{
				if (depth < wc->max_depth && sdir->d_type == DT_DIR)
				{
					_recdir(shell, wc, sdir, pathopen, depth);
				}
				else if (depth == wc->max_depth)
				{
					savepath(shell, wc, sdir, pathopen, depth);
				}
				sdir = readdir(dirp);
			}
			closedir(dirp);
		}
	}
}
