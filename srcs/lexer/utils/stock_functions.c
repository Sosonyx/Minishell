/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stock_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:07:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 14:08:38 by ihadj            ###   ########.fr       */
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

static void	handle_quote(char c, char *quote, int *sq, int *dq)
{
	if (!*quote)
	{
		*quote = c;
		if (c == '\'')
			*sq += 1;
		else
			*dq += 1;
	}
	else if (*quote == c)
		*quote = 0;
}

static int	should_stop(char c, char quote)
{
	if (!quote && (ft_isspace(c) || is_special(c)))
		return (1);
	return (0);
}

int	stock_word(t_token **tokens, int j, char *line, int *i)
{
	int		start;
	char	quote;
	int		sq;
	int		dq;

	start = *i;
	quote = 0;
	sq = 0;
	dq = 0;
	while (line[*i])
	{
		if (line[*i] == '\'' || line[*i] == '"')
			handle_quote(line[*i], &quote, &sq, &dq);
		else if (should_stop(line[*i], quote))
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
