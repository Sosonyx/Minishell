/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:07:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/31 15:48:05 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stock_special(t_token **tokens, int j, char *line, int *i)
{
	int	len;

	len = special_len(line, *i);
	if (len == -1)
	{
		tokens[j++] = create_token(ft_strndup(&line[*i], 1), \
				T_INCORRECT, false, false);
		*i += 1;
		return (j);
	}
	tokens[j++] = create_token(ft_strndup(&line[*i], len), \
				get_token_type(&line[*i]), false, false);
	*i += len;
	return (j);
}

int	stock_word(t_token **tokens, int j, char *line, int *i)
{
	int		start;
	char	c;	
	char	quote;
	int		sq;
	int		dq;

	start = *i;
	quote = 0;
	sq = 0;
	dq = 0;
	while (line[*i])
	{
		c = line[*i];
		if (c == '\'' || c == '"')
		{
			if (!quote)
			{
				quote = c;
				if (c == '\'')
					sq = 1;
				else
					dq = 1;
				(*i)++;
				continue ;
			}
			if (quote == c)
			{
				quote = 0;
				(*i)++;
				continue ;
			}
		}
		if (!quote && (ft_isspace(c) || is_special(c)))
			break ;
		(*i)++;
	}
	if (quote)
		return (-1);
	if (*i > start)
		tokens[j++] = create_token(ft_strndup(&line[start], (*i - start)),
				T_WORD, sq, dq);
	return (j);
}

int	stock_quoted(t_token **tokens, int j, char *line, int *i)
{
	char	quote;
	int		start;

	quote = line[*i];
	(*i)++;
	start = *i;
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (!line[*i])
		return (-1);
	tokens[j++] = create_token(ft_strndup(&line[start], (*i - start)), \
				T_WORD, (quote == '\''), (quote == '"'));
	(*i)++;
	return (j);
}

