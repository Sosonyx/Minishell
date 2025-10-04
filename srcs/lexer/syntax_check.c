/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:15:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/04 16:35:38 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	syntax_err(const char *near)
{
	if (!near)
		near = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)near, 2);
	ft_putstr_fd("'\n", 2);
}

static int	parenth_checker(t_token **toks, int i)
{
	int	lp;
	int	rp;
	int	last;

	last = 0;
	lp = 0;
	rp = 0;
	while (toks[i])
	{
		if (toks[i]->type == T_LPARENT)
			lp++;
		else if (toks[i]->type == T_RPARENT)
			rp++;
		if (rp > lp)
			return (syntax_err(toks[i]->val), -1);
		i++;
	}
	if (lp != rp)
	{
		while (i-- && !is_parenth(toks[i]->type))
			;
		return (syntax_err(toks[i]->val), -1);
	}
	return (1);
}

static int	is_valid_start(t_token **toks)
{
	if (!toks || !toks[0])
		return (1);
	if (is_pipe(toks[0]->type))
		return (syntax_err(toks[0]->val), 0);
	else if (toks[0]->type == T_AND)
		return (syntax_err(toks[0]->val), 0);
	else if (toks[0]->type == T_OR)
		return (syntax_err(toks[0]->val), 0);
	if (parenth_checker(toks, 0) == -1)
		return (0);
	return (1);
}

int	check_syntax(t_token **toks)
{
	int			i;
	t_toktype	cur;

	i = -1;
	if (!is_valid_start(toks))
		return (0);
	while (toks[++i])
	{
		cur = toks[i]->type;
		if (!_control_op(cur, toks, i))
			return (0);
		if (! _redir(cur, toks, i))
			return (0);
		if (!_lparenth(cur, toks, i))
			return (0);
		if (!_is_word(cur, toks, i))
			return (0);
	}
	return (1);
}
