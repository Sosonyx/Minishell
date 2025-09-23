/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 19:37:11 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static char	**rebuild_cmd_args(t_wildcard_p wc, char **cmd_args)
{
	char	**new_args;
	int		n;
	int		failed;
	
	new_args = calloc((wc->totalmatches + 2), sizeof(char *));
	if (new_args)
	{
		*new_args = ft_strdup(*cmd_args);
		n = 1;
		failed = 0;
		while (n <= wc->totalmatches)
		{
			new_args[n] = ft_strdup(wc->matches[n - 1]);
			if (!new_args[n++])
				failed = 1;
		}
		if (!failed)
			ft_split_free(cmd_args);
		else
		{
			ft_split_free(new_args);
			return (cmd_args);
		}
	}
	return (new_args);
}

static void	wcconfig(t_wildcard_p wc, char *path)
{
	char	**dir;

	wc->spath = ft_split(path, '/');
	dir = wc->spath;
	while (*dir++)
		++wc->max_depth;
	--wc->max_depth;
	while (*path)
		path++;
	wc->lastisdir = (*(path - 1) == '/');	
}

void	_wildcard_expand(t_wildcard_p wc, char *path)
{
	wcconfig(wc, path);	
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
			{
				if (iswildcard(*commands))
					_wildcard_expand(wc, *commands);
				else
					addmatch(wc, *commands);
				commands++;
			}
			sortmatches(wc);
			*cmd_args = rebuild_cmd_args(wc, *cmd_args);
			free(wc);
		}
	}
}
