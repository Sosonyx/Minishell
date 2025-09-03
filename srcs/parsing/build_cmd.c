/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/03 15:01:04 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_tok_word(t_tok_container_p tok_container, int i)
{
	int			words;
	t_token_p	tok;

	words = 0;
	tok = tok_container->tokens[i];	
	while (tok_container->tokens[i++])
	{
		if (tok->type == T_WORD)
			words++;
	}
	return (words);
}

t_error_status	build_cmd(char ***cmd, t_tok_container_p tok_container, int i)
{
	t_token_p	tok;
	int			words;
	int			j;
	
	j = 0;
	*cmd = ft_calloc((count_tok_word(tok_container, i) + 1), sizeof(char *));
	if (!*cmd)
		return (RETURN_FAIL);
	tok = tok_container->tokens[i];
	while (tok && (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT || tok->type == T_WORD))
	{
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT)
			i++;
		else
		{
			(*cmd)[j] = ft_strdup(tok->val);
			// if (!cmd[j])
			// 	free ;
			i++;
			j++;
		}
		tok = tok_container->tokens[i];
	}
	(*cmd)[j] = NULL;
	return (RETURN_OK);
}
