/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_external_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/04 11:22:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_status	find_external_cntl_and_or(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
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

t_error_status	find_external_cntl_pipe(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	t_token_p	cur_token;
	int			n = 0;
	int			in_parenthesis = 0;
	
	*op = ft_calloc(1, sizeof(t_ast));
	if (*op)
	{
		while (tok_container->tokens[start] && start <= end)
		{
			cur_token = tok_container->tokens[start];
			if (cur_token->type == T_PIPE && !in_parenthesis)
			{
				(*op)->type = OP_PIPE;
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

t_error_status	find_external_parenthesis(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	int			n = 0;
	int			subshell_end = 0;

	if (tok_container->tokens[start] && (tok_container->tokens[start])->type == T_LPARENT)
	{
		subshell_end = end - 1;
		while (tok_container->tokens[subshell_end] && tok_container->tokens[subshell_end]->type != T_RPARENT && subshell_end <= end)
			subshell_end--;
		*op = ft_calloc(1, sizeof(t_ast));
		if (*op)
		{
			// tok_container->op_index++;
			(*op)->type = OP_SUBSHELL;
			free(tok_container->tokens[start]);
			tok_container->tokens[start] = NULL;
			free(tok_container->tokens[subshell_end]);
			tok_container->tokens[subshell_end] = NULL;
			(*op)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
			if ((*op)->cntl_op)
			{
				build_ast(&(*op)->cntl_op->left, tok_container, ++start, subshell_end, LEFT_BRANCH, 1);
				return (RETURN_OK);
			}			
		}
	}
	return (RETURN_FAIL);	
}
