/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/05 13:11:56 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/12 13:26:27 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_len(const char *line, int i)
{
	if (line[i] == '|')
	{
		if (line[i + 1] == '|')
			return (2);
		return (1);
	}
	else if (line[i] == '<')
	{
		if (line[i + 1] == '<')
			return (2);
		return (1);
	}
	else if (line[i] == '>')
	{
		if (line[i + 1] == '>')
			return (2);
		return (1);
	}
	else if (line[i] == '(' || line[i] == ')')
		return (1);
	else if (line[i] == '&' && line[i + 1] == '&')
		return (2);
	return (1);
}

static void	skip_quote(char *line, int *i, int *words)
{
	char	quote;

	quote = line[(*i)++];
	while (line[*i] && line[*i] != quote)
		(*i)++;
	if (line[*i] == quote)
		(*i)++;
	(*words)++;
}

static int	parse_line(char *line, int *i, int *words)
{
	int	len;

	while (line[*i] && ft_isspace(line[*i]))
		(*i)++;
	if (!line[*i])
		return (0);
	if (is_special(line[*i]))
	{
		len = special_len(line, *i);
		(*words)++;
		*i += len;
	}
	else if (line[*i] == '\'' || line[*i] == '"')
		skip_quote(line, i, words);
	else
	{
		while (line[*i] && !ft_isspace(line[*i]) && \
		!is_special(line[*i]) && line[*i] != '\'' && line[*i] != '"')
			(*i)++;
		(*words)++;
	}
	return (1);
}

int	count_tokens(char *line)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	if (!line || !line[0])
		return (0);
	while (line[i])
		if (!parse_line(line, &i, &words))
			break ;
	return (words);
}
