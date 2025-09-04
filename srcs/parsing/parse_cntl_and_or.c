/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cntl_and_or.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:55 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/04 16:35:27 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_status	parse_cntl_and_or(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	t_token_p			cur_token;
	int					in_parenthesis = 0;
	t_tok_container_p	tok_copy = tok_container;
	
	*op = ft_calloc(1, sizeof(t_ast));
	if (*op)
	{
		while (tok_container->tokens[start] && start <= end)
		{
			cur_token = tok_container->tokens[start];
			if (cur_token->type == T_AND && !in_parenthesis)
			{
				(*op)->type = OP_AND;
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK) ;
			}
			else if (cur_token->type == T_OR && !in_parenthesis)
			{
				(*op)->type = OP_OR;
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK) ;
			}
			else if (cur_token->type == T_LPARENT && !in_parenthesis)
				in_parenthesis = 1;
			else if (cur_token->type == T_RPARENT && in_parenthesis)
				in_parenthesis = 0;
			start++;
		}
		free(*op);
		*op = NULL;
	}
	return (RETURN_FAIL);
}
