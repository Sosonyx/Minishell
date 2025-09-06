/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cntl_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 14:53:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_return_status	parse_cntl_pipe(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	t_token_p	cur_token;
	int			in_parenthesis;
	int			n;

	n = 0;
	in_parenthesis = 0;
	*op = ft_calloc(1, sizeof(t_ast));
	if (*op)
	{
		while (tok_container->tokens[start] && start <= end)
		{
			cur_token = tok_container->tokens[start];
			if (cur_token->type == T_PIPE && !in_parenthesis)
			{
				(*op)->type = OP_PIPE;
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK);
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
