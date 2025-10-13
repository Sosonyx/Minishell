/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/10/13 19:17:56 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static void	rebuild_args(t_shell_p shell, \
	t_wildcard_p wc, t_ast_p ast, t_redir_p redir)
{
	if (wc->matches)
	{
		if (!redir)
		{
			ft_split_free(ast->leaf->cmds);
			ast->leaf->cmds = wc->matches;
		}
		else
		{
			if (wc->totalmatches > 1)
			{
				ast->leaf->abort = true;
				print_cmd_error2(shell, redir->target, AMBIG_REDIR_ERRMSG);
				ft_split_free(wc->matches);
			}
			else if (wc)
			{
				free(redir->target);
				redir->target = *wc->matches;
				free(wc->matches);
			}
		}
		wc->matches = NULL;
		wc->totalmatches = 0;
	}
}

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

void	aggregate_matches(t_shell_p shell, t_wildcard_p wc, char *args)
{
	char	**matches;

	matches = _calloc(shell, wc->totalmatches + \
		wc->tmp_totalmatches + 2, sizeof(char *));
	if (!matches)
		return ;
	ft_memcpy(matches, wc->matches, wc->totalmatches * sizeof(char *));
	if (wc->tmp_matches)
	{
		ft_memcpy(matches + wc->totalmatches, \
			wc->tmp_matches, wc->tmp_totalmatches * sizeof(char *));
		free(wc->tmp_matches);
		wc->tmp_matches = NULL;
		wc->totalmatches += wc->tmp_totalmatches;
		wc->tmp_totalmatches = 0;
	}
	else
	{
		matches[wc->totalmatches] = remove_quotes(shell, \
			NULL, _strdup(shell, args));
		++wc->totalmatches;
	}
	free(wc->matches);
	wc->matches = matches;
}

void	_expand(t_shell_p shell, t_wildcard_p wc, char *arg)
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

static void	_wildcard_expand(t_shell_p shell, t_wildcard_p wc, \
	void **args, int mode)
{
	if (mode == 1)
	{
		if (**((char **)args) == '/')
			wc->isstartdir = true;
		_expand(shell, wc, *((char **) args));
	}
	else if (mode == 2)
	{
		if (*((t_redir_p)*args)->target == '/')
			wc->isstartdir = true;
		_expand(shell, wc, ((t_redir_p)*args)->target);
	}
}

void	wildcard_expand(t_shell_p shell, t_ast_p ast)
{
	t_wildcard_p	wc;
	void			**args;

	wc = _calloc(shell, 1, sizeof(struct s_wildcard));
	if (wc)
	{
		if (ast->leaf->cmds && *ast->leaf->cmds)
		{
			args = (void **) ast->leaf->cmds;
			while (*((char **) args))
				_wildcard_expand(shell, wc, args++, 1);
			if (wc->totalmatches)
				rebuild_args(shell, wc, ast, NULL);
		}
		args = (void **) &ast->leaf->redir;
		while ((t_redir_p)*args && !ast->leaf->abort)
		{
			_wildcard_expand(shell, wc, args, 2);
			if (wc->totalmatches)
				rebuild_args(shell, wc, ast, (t_redir_p)*args);			
			args = (void **) &(((t_redir_p)*args)->next);
		}
		free(wc);
	}
}
