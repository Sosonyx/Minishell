/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:33:35 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/01 15:33:36 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *val, t_toktype type, bool sq, bool dq)
{
	t_token	*tok;

	tok = ft_calloc(1, sizeof(*tok));
	if (!tok)
		return (NULL);
	tok->val = val;
	tok->type = type;
	tok->was_single_quoted = sq;
	tok->was_double_quoted = dq;
	return (tok);
}

t_toktype	get_token_type(const char *line)
{
	if (!line)
		return (T_WORD);
	if (line[0] == '|' && line[1] == '|')
		return (T_OR);
	if (line[0] == '|')
		return (T_PIPE);
	if (line[0] == '<' && line[1] == '<')
		return (T_HEREDOC);
	if (line[0] == '>' && line[1] == '>')
		return (T_APPEND);
	if (line[0] == '<')
		return (T_REDIR_IN);
	if (line[0] == '>')
		return (T_REDIR_OUT);
	if (line[0] == '(')
		return (T_LPARENT);
	if (line[0] == ')')
		return (T_RPARENT);
	if (line[0] == '&' && line[1] == '&')
		return (T_AND);
	return (T_WORD);
}

static void	skip_spaces(char *line, int *i)
{
	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
}

static int	fill_tokens(t_token **tokens, char *line)
{
	int	i;
	int	j;
	int	ret;

	i = 0;
	j = 0;
	while (line[i])
	{
		skip_spaces(line, &i);
		if (!line[i])
			break ;
		if (is_special(line[i]))
			j = stock_special(tokens, j, line, &i);
		else
		{
			ret = stock_word(tokens, j, line, &i);
			if (ret == -1)
			{
				ft_putstr_fd(EOF_ERRMSG, 2);
				return (0);
			}
			j = ret;
		}
	}
	return (tokens[j] = NULL, j);
}

int stock_tokens(t_tok_container *t, char *line)
{
	int words;

	words = count_tokens(line);
	t->tokens = ft_calloc(words + 1, sizeof(t_token *));
	if (!t->tokens)
		return (0);
	return (fill_tokens(t->tokens, line));
}
