/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   savepath.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:22:28 by fox               #+#    #+#             */
/*   Updated: 2025/10/06 15:10:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static char	*getfullpath(t_minishell_p shell, t_wildcard_p wc, struct dirent *sdir, char *path)
{
	char	*tmp;

	if (path)
	{
		path = catpath(shell, path, sdir->d_name);
		if (path && wc->lastisdir)
		{
			tmp = path;
			path = catpath(shell, path, NULL);
			free(tmp);
		}
	}
	return (path);
}

void	savepath(t_minishell_p shell, t_wildcard_p wc, struct dirent *sdir, char *path, int depth)
{
	char	**ptr;
	char	*tmp;

	if (ishidden(sdir->d_name) || (sdir->d_type == DT_REG && wc->lastisdir) || skipdotdotdot(sdir->d_name, wc->spath[depth]))
		return ;
	if (pathmatch(sdir->d_name, wc->spath[depth]))
	{
		path = getfullpath(shell, wc, sdir, path);
		if (path && !ishidden(path))
			addmatch(shell, wc, path);
		free(path);
	}
}
