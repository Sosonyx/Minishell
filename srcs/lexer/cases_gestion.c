/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:07:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/24 19:25:13 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stock_special(t_token **tokens, int j, const char *line, int *i)
{
	int	len;

	len = special_len(line, *i);
	tokens[j++] = create_token(ft_strndup(&line[*i], len), \
				get_token_type(&line[*i]), false, false);
	*i += len;
	return (j);
}

int	stock_word(t_token **tokens, int j, const char *line, int *i)
{
	int	start;

	start = *i;
	while (line[*i] && !ft_isspace((unsigned char)line[*i]) \
			&& !is_special(line[*i]) && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	tokens[j++] = create_token(ft_strndup(&line[start], (size_t)(*i - start)), \
				T_WORD, false, false);
	return (j);
}

int	stock_quoted(t_token **tokens, int j, const char *line, int *i)
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

