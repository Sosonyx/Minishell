/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 13:05:23 by fox               #+#    #+#             */
/*   Updated: 2025/09/17 20:04:16 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_redir_p	build_redir(t_tok_container_p tok_container, int i, int end)
{
	t_redir_p	head;
	t_redir_p	curr;
	t_redir_p	new;
	t_token_p	tok;

	head = NULL;
	curr = NULL;
	while (i <= end && tok_container->tokens[i])
	{
		tok = tok_container->tokens[i];
		if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT
			|| tok->type == T_APPEND || tok->type == T_HEREDOC)
		{
			new = ft_calloc(1, sizeof(t_redir));
			if (!new)
				return (head);
			if (tok->type == T_REDIR_IN)
				new->type = R_IN;
			else if (tok->type == T_REDIR_OUT)
				new->type = R_OUT;
			else if (tok->type == T_APPEND)
				new->type = R_APPEND;
			else
				new->type = R_HDOC;
			if (new->type == R_HDOC)
				new->limiter = ft_strdup(tok_container->tokens[i + 1]->val);
			else
				new->target = ft_strdup(tok_container->tokens[i + 1]->val);
			free(tok_container->tokens[i]);
			tok_container->tokens[i] = NULL;
			free(tok_container->tokens[i + 1]);
			tok_container->tokens[i + 1] = NULL;
			if (!head)
				head = new;
			else
				curr->next = new;
			curr = new;
			i += 2;
			continue ;
		}
		i++;
	}
	return (head);
}
