/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/10/07 14:45:14 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	rebuild_cmd_args(t_wildcard_p wc, char ***cmd_args)
{
	if (wc->matches)
	{
		ft_split_free(*cmd_args);
		*cmd_args = wc->matches;
	}
}

static void	wcconfig(t_shell_p shell, t_wildcard_p wc, char *path)
{
	char	**dir;

	wc->startbydot = false;
	wc->spath = _split(shell, path, '/');
	dir = wc->spath;
	wc->max_depth = 0;
	while (*dir++)
		++wc->max_depth;
	--wc->max_depth;
	while (*path)
		path++;
	wc->lastisdir = (*(path - 1) == '/');
}

void	aggregate_matches(t_shell_p shell, t_wildcard_p wc, char *args)
{
	char	**matches;

	matches = _calloc(shell, wc->totalmatches + wc->tmp_totalmatches + 2, sizeof(char *));
	if (matches)
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
		matches[wc->totalmatches] = remove_quotes(shell, NULL, _strdup(shell, args));
		++wc->totalmatches;
	}
	free(wc->matches);
	wc->matches = matches;
}

void	_wildcard_expand(t_shell_p shell, t_wildcard_p wc, char *arg)
{
	if (iswildcard(arg))
	{
		wcconfig(shell, wc, arg);
		if (is_no_abort(shell) && wc->spath)
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
	}
	else
		addmatch(shell, wc, arg);
	if (is_no_abort(shell))
	{
		sortmatches(wc);
		aggregate_matches(shell, wc, arg);		
	}
	
}

void	wildcard_expand(t_shell_p shell, t_ast_p ast)
{
	t_wildcard_p	wc;
	char			**args;
	char			**expanded_args;

	if (*ast->leaf->cmds && **ast->leaf->cmds)
	{
		args = ast->leaf->cmds;
		wc = _calloc(shell, 1, sizeof(struct s_wildcard));
		if (wc)
		{
			while (*args)
			{
				if (**args == '/')
					wc->isstartdir = true;
				_wildcard_expand(shell, wc, *args++);
			}
			if (wc->totalmatches)
			{
				rebuild_cmd_args(wc, &ast->leaf->cmds);
			}
			free(wc);
		}
	}
}
