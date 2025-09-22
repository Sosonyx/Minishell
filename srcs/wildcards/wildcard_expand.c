/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/09/21 21:07:18 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

int		recdepth(char **spath)
{
	int	depth;

	depth = 0;
	while (*spath++)
		++depth;
	return (depth - 1);
}

void	_wildcard_expand(t_wildcard_p wc, char *path)
{
	wc->spath = ft_split(path, '/');
	if (wc->spath)
	{
		wc->max_depth = recdepth(wc->spath);
		if (iswildcard(*wc->spath))
			recdir(wc, ".", 1);
		else
			recdir(wc, *wc->spath, 1);
		ft_split_free(wc->spath);
	}
}

static char	**rebuild_cmd_args(t_wildcard_p wc, char **cmd_args)
{
	char	**new_args;
	int		n;
	int		failed;
	
	new_args = calloc((wc->totalmatches + 2), sizeof(char *));
	if (new_args)
	{
		*new_args = strdup(*cmd_args);
		n = 1;
		failed = 0;
		while (n <= wc->totalmatches)
		{
			new_args[n] = strdup(wc->matches[n - 1]);
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

void	wildcard_expand(char ***cmd_args)
{
	t_wildcard_p	wc;
	char			**commands;
	char			**expanded_args;
	
	if (*cmd_args && **cmd_args)
	{
		commands = *cmd_args;
		wc = calloc(1, sizeof(struct s_wildcard));
		if (wc)
		{
			while (*commands)
				_wildcard_expand(wc, *commands++);
				
			sortmatches(wc);
			*cmd_args = rebuild_cmd_args(wc, *cmd_args);
			// printargs(wc);
			free(wc);
		}
	}
}
