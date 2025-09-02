/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_redir.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:02:26 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/02 17:03:52 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

t_redir_p build_redir(t_tok_container_p tok_container, int i)
{
	t_token_p tok;
    t_redir_p head;
    t_redir_p new;

	head = NULL;
    while (tok_container->tokens[i])
    {
		tok = tok_container->tokens[i];
        if (tok->type == T_REDIR_IN || tok->type == T_REDIR_OUT ||
            tok->type == T_APPEND || tok->type == T_HEREDOC)
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
            else if (tok->type == T_HEREDOC)
                new->type = R_HDOC;
            if (tok_container->tokens[i + 1] &&
                tok_container->tokens[i + 1]->type == T_WORD)
            {
                new->target = ft_strdup(tok_container->tokens[i + 1]->val);
                i++;
            }
            new->next = head;
            head = new;
        }
        else
            break;
        i++;
    }
    return (head);
}
