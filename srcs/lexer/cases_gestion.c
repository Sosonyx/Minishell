/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cases_gestion.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:07:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/25 20:45:08 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	stock_special(t_token **tokens, int j, char *line, int *i)
{
	int	len;

	len = special_len(line, *i);
	tokens[j++] = create_token(ft_strndup(&line[*i], len), \
				get_token_type(&line[*i]), false, false);
	*i += len;
	return (j);
}

int	stock_word(t_token **tokens, int j, char *line, int *i)
{
	int		start;
	char	quote;
	char	*res;
	int		k;


	start = *i;
	while (line[*i] && !ft_isspace(line[*i]) && line[*i] != '\'' && line[*i] != '"')
		(*i)++;
	
	if (line[*i] == '\'' || line[*i] == '"')
	{
		quote = line[*i];
		(*i)++;
		///////////////////////////////////////////////////////////////
		while (line[*i] && !ft_isspace(line[*i]))
		{
			while (line[*i] && line[*i] != quote)
				(*i)++;
			// if (!line[*i])
			// 	// break ;
			// 	return (-1);
			(*i)++;
		}
		///////////////////////////////////////////////////////////////
		res = malloc(sizeof(char) * (*i - start - 1));
		if (!res)
			return (-1);
		k = 0;
		while (start < *i - 1)
		{
			if (line[start] == quote)
				start++;
			res[k++] = line[start++];
		}
		res[k] = 0;
		tokens[j++] = create_token(res, T_WORD, (quote == '\''), (quote == '"'));
		return (j);
	}
	tokens[j++] = create_token(ft_strndup(&line[start], (*i - start)), \
				T_WORD, (quote == '\''), (quote == '"'));
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

