/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   _expand.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:02:05 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 15:16:34 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	wcconfig(t_shell_p shell, t_wildcard_p wc, char *path)
{
	char	**dir;

	wc->startbydot = false;
	wc->spath = _split(shell, path, '/');
	if (wc->spath)
	{
		dir = wc->spath;
		wc->max_depth = 0;
		while (*dir++)
			++wc->max_depth;
		--wc->max_depth;
		while (*path)
			path++;
		wc->lastisdir = (*(path - 1) == '/');
	}
}

static void	run_recdir(t_shell_p shell, t_wildcard_p wc)
{
	if (iswildcard(*wc->spath))
	{
		if (wc->isstartdir)
		{
			recdir(shell, wc, "/", 0);
			wc->isstartdir = false;
		}
		else
		{
			wc->startbydot = true;
			recdir(shell, wc, ".", 0);
		}
	}
	else if (wc->isstartdir)
	{
		recdir(shell, wc, _strjoin(shell, "/", *wc->spath), 1);
		wc->isstartdir = false;
	}
	else
	{
		recdir(shell, wc, *wc->spath, 1);
	}
	ft_split_free(wc->spath);
}

void	_expand(t_shell_p shell, t_wildcard_p wc, char *arg)
{
	if (iswildcard(arg))
	{
		wcconfig(shell, wc, arg);
		if (is_no_abort(shell) && wc->spath)
			run_recdir(shell, wc);
	}
	else
	{
		arg = remove_quotes(shell, NULL, _strdup(shell, arg));
		addmatch(shell, wc, arg);
	}
	if (is_no_abort(shell))
	{
		sortmatches(wc);
		aggregate_matches(shell, wc, arg);
	}
}
