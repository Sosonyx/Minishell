/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:22:28 by fox               #+#    #+#             */
/*   Updated: 2025/10/21 17:16:45 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	onlydir(t_wildcard_p wc)
{
	return (wc->sdir->d_type == DT_REG && wc->lastisdir);
}

static char	*getfullpath(t_shell_p shell, t_wildcard_p wc, char *path)
{
	char	*tmp;

	if (path)
	{
		path = catpath(shell, path, wc->sdir->d_name);
		if (path && wc->lastisdir)
		{
			tmp = path;
			path = catpath(shell, path, NULL);
			free(tmp);
		}
	}
	return (path);
}

void	savepath(t_shell_p shell, t_wildcard_p wc, char *path, int depth)
{
	if (ishidden(wc->sdir->d_name) || onlydir(wc) || \
	skipdotdotdot(wc->sdir->d_name, wc->spath[depth]))
		return ;
	if (pathmatch(wc->sdir->d_name, wc->spath[depth], 0))
	{
		path = getfullpath(shell, wc, path);
		if (path && !ishidden(path))
			addmatch(shell, wc, path);
		free(path);
	}
}
