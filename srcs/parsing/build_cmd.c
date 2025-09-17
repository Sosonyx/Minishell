/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:06:53 by fox               #+#    #+#             */
/*   Updated: 2025/09/17 13:07:10 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tok_word(t_tok_container_p tok_container, int i, int end)
{
	int			words;
	t_token_p	tok;

	words = 0;
	tok = tok_container->tokens[i];	
	while (i <= end && tok_container->tokens[i])
	{
		tok = tok_container->tokens[i];			
		if (tok->type == T_WORD)
			words++;
		i++;			
	}
	return (words);
}

int	build_cmd(char ***cmd, t_tok_container_p tok_container, int start, int end)
{
	int			words;
	int			j;
	int			i;
	t_token_p	tok;

	words = count_tok_word(tok_container, start, end);
	*cmd = ft_calloc(words + 1, sizeof(char *));
	if (!*cmd)
		return (RETURN_FAIL);
	j = 0;
	i = start;
	while (i <= end)
	{
		tok = tok_container->tokens[i];
		if (tok && tok->type == T_WORD)
		{
			(*cmd)[j++] = ft_strdup(tok->val);
			free(tok->val);
			free(tok);
			tok_container->tokens[i] = NULL;
		}
		i++;
	}
	return (RETURN_OK);
}
