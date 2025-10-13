/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_token.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:29:43 by sosony            #+#    #+#             */
/*   Updated: 2025/10/13 16:35:25 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_control_op(t_toktype cur, t_token **toks, int i)
{
	if (is_control_op(cur) && toks[i + 1] && \
	(is_control_op(toks[i + 1]->type) || is_parenth(toks[i + 1]->type) == 2))
	{
		syntax_err(toks[i + 1]->val);
		return (0);
	}
	if (is_control_op(cur) && !toks[i + 1])
	{
		syntax_err(NULL);
		return (0);
	}
	return (1);
}

int	_redir(t_toktype cur, t_token **toks, int i)
{
	if (is_redir(cur))
	{
		if (!toks[i + 1] || toks[i + 1]->type != T_WORD)
		{
			if (toks[i + 1])
				syntax_err(toks[i + 1]->val);
			else
				syntax_err(NULL);
			return (0);
		}
	}
	return (1);
}

int	_lparenth(t_toktype cur, t_token **toks, int i)
{
	if (is_parenth(cur) == 1)
	{
		if (!toks[i + 1] || is_parenth(toks[i + 1]->type) == 2 || \
			is_control_op(toks[i + 1]->type))
		{
			syntax_err(toks[i + 1]->val);
			return (0);
		}
	}
	return (1);
}

int	_rparenth(t_toktype cur, t_token **toks, int i)
{
	if (is_parenth(cur) == 2)
	{
		if (toks[i + 1] && (is_parenth(toks[i + 1]->type) == 1 || \
			is_word(toks[i + 1]->type)))
		{
			syntax_err(toks[i + 1]->val);
			return (0);
		}
	}
	return (1);
}

int	_is_word(t_toktype cur, t_token **toks, int i)
{
	if (is_word(cur))
	{
		if (toks[i + 1] && is_parenth(toks[i + 1]->type) == 1)
		{
			syntax_err(toks[i + 2]->val);
			return (0);
		}
	}
	return (1);
}
