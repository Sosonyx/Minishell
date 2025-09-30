/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/09/30 16:01:17 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	rebuild_cmd_args(t_wildcard_p wc, char ***cmd_args)
{
	char	**new_args;
	int		n;
	int		failed;
	
	new_args = ft_calloc((wc->totalmatches + 2), sizeof(char *));
	if (new_args)
	{
		*new_args = ft_strdup(**cmd_args);
		n = 1;
		failed = 0;
		while (n <= wc->totalmatches)
		{
			new_args[n] = ft_strdup(wc->matches[n - 1]);
			if (!new_args[n++])
				failed = 1;
		}
		ft_split_free(wc->matches);
		if (!failed)
		{
			*cmd_args = new_args;
		}
		else
			ft_split_free(new_args);
	}
}

static void	wcconfig(t_wildcard_p wc, char *path)
{
	char	**dir;

	wc->startbydot = false;
	wc->spath = ft_split(path, '/');
	dir = wc->spath;
	wc->max_depth = 0;
	while (*dir++)
		++wc->max_depth;
	--wc->max_depth;
	while (*path)
		path++;
	wc->lastisdir = (*(path - 1) == '/');	
}

void	aggregate_matches(t_wildcard_p wc, char *command)
{
	char	**matches;

	matches = ft_calloc(wc->totalmatches + wc->tmp_totalmatches + 2, sizeof(char *));
	if (!matches)
		return ;
	ft_memcpy(matches, wc->matches, wc->totalmatches * sizeof(char *));

	if (wc->tmp_matches)
	{
		ft_memcpy(matches + wc->totalmatches, wc->tmp_matches, wc->tmp_totalmatches * sizeof(char *));
		free(wc->tmp_matches);
		wc->tmp_matches = NULL;
		wc->totalmatches += wc->tmp_totalmatches;
		wc->tmp_totalmatches = 0;
	}
	else
	{
		matches[wc->totalmatches] = command;
		++wc->totalmatches;
	}
	free(wc->matches);
	wc->matches = matches;	
}

void	_wildcard_expand(t_wildcard_p wc, char *command)
{
	if (iswildcard(command))
	{
		wcconfig(wc, command);	
		if (wc->spath)
		{
			if (iswildcard(*wc->spath))
			{
				wc->startbydot = true;
				recdir(wc, ".", 0);
			}
			else
				recdir(wc, *wc->spath, 1);
			ft_split_free(wc->spath);
		}
	}
	else
	{
		addmatch(wc, command);
	}
	sortmatches(wc);
	aggregate_matches(wc, command);
}

void	wildcard_expand(char ***cmd_args)
{
	t_wildcard_p	wc;
	char			**commands;
	char			**expanded_args;

	if (*cmd_args && **cmd_args)
	{
		commands = *cmd_args + 1;
		wc = ft_calloc(1, sizeof(struct s_wildcard));
		if (wc)
		{
			while (*commands)
				_wildcard_expand(wc, *commands++);
			if (wc->totalmatches)
				rebuild_cmd_args(wc, cmd_args);
			free(wc);
		}
	}
}
