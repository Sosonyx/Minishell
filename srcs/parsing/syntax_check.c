/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_check.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 13:15:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/24 18:45:56 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_pipe(t_toktype t)
{
	return (t == T_PIPE);
}

static int	is_redir(t_toktype t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_APPEND || t == T_HEREDOC);
}

static void	syntax_err(const char *near)
{
	if (!near)
		near = "newline";
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	ft_putstr_fd((char *)near, 2);
	ft_putstr_fd("'\n", 2);
}

// static int	quote_count(t_token **toks)
// {
// 	int			i;
// 	int			sq_count;
// 	int			dq_count;
// 	t_toktype	cur;

// 	i = 0;
// 	while (toks[i])
// 	{
// 		if (toks[i]->was_single_quoted == true)
// 			sq_count++;
// 		else if (toks[i]->was_double_quoted == true)
// 			dq_count++;
// 		i++;
// 	}
// }

int	check_syntax(t_token **toks)
{
	int			i;
	t_toktype	cur;

	i = 0;
	if (!toks || !toks[0])
		return (1);
	if (is_pipe(toks[0]->type))
		return (syntax_err(toks[0]->val), 0);
	while (toks[i])
	{
		cur = toks[i]->type;
		if (is_pipe(cur))
		{
			if (!toks[i + 1])
			{
				if (toks[i + 1])
					syntax_err(toks[i + 1]->val);
				else
					syntax_err(NULL);
				return (0);
			}
		}
		else if (is_redir(cur))
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
		i++;
	}
	return (1);
}
