/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/09/30 20:50:28 by cgajean          ###   ########.fr       */
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
		matches[wc->totalmatches] = ft_strdup(command);
		++wc->totalmatches;
	}
	free(wc->matches);
	wc->matches = matches;	
}

void	_wildcard_expand(t_minishell_p shell, t_wildcard_p wc, char *command)
{
	if (iswildcard(command))
	{
		wcconfig(wc, command);	
		if (wc->spath)
		{
			if (iswildcard(*wc->spath))
			{
				if (wc->isstartdir)
				{
					recdir(wc, "/", 0);
					wc->isstartdir = false;					
				}
				else
				{
					wc->startbydot = true;
					recdir(wc, ".", 0);
				}
			}
			else if (wc->isstartdir)
			{
				recdir(wc, ft_strjoin("/", *wc->spath), 1);
				wc->isstartdir = false;
			}
			else
			{
				recdir(wc, *wc->spath, 1);
			}
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

void	wildcard_expand(t_minishell_p shell, t_ast_p ast)
{
	t_wildcard_p	wc;
	char			**commands;
	char			**expanded_args;

	if (*ast->leaf->cmds && **ast->leaf->cmds)
	{
		commands = ast->leaf->cmds;
		wc = ft_calloc(1, sizeof(struct s_wildcard));
		if (wc)
		{
			while (*commands)
			{
				if (**commands == '/')
					wc->isstartdir = true;
				_wildcard_expand(shell, wc, *commands++);
			}
			if (wc->totalmatches)
			{
				rebuild_cmd_args(wc, &ast->leaf->cmds);
			}
			free(wc);
		}
		else
			set_abort(shell, MEM_ERRMSG);
	}
}
