/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard_expand.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:27:10 by fox               #+#    #+#             */
/*   Updated: 2025/10/17 19:30:24 by ihadj            ###   ########.fr       */
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
				prt_err(shell, redir->target, AMBIG_REDIR_ERRMSG);
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
		if (*((t_redir_p)(*args))->target == '/')
			wc->isstartdir = true;
		_expand(shell, wc, ((t_redir_p)(*args))->target);
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
		while ((t_redir_p)(*args) && !ast->leaf->abort)
		{
			_wildcard_expand(shell, wc, args, 2);
			if (wc->totalmatches)
				rebuild_args(shell, wc, ast, (t_redir_p)(*args));
			args = (void **) &(((t_redir_p)(*args))->next);
		}
		free(wc);
	}
}
