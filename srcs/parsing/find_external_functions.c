/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_external_functions.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:45 by cgajean           #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2025/09/03 16:44:30 by ihadj            ###   ########.fr       */
=======
/*   Updated: 2025/09/03 15:56:41 by cgajean          ###   ########.fr       */
>>>>>>> ef9d9dae428d70487b58b75ef98fc608600b6700
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
<<<<<<< HEAD
				return (tok_container->op_index = start, RETURN_OK) ;
=======
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK) ;
>>>>>>> ef9d9dae428d70487b58b75ef98fc608600b6700
			}
			else if (cur_token->type == T_OR && !in_parenthesis)
			{
				(*op)->type = OP_OR;
<<<<<<< HEAD
				return (tok_container->op_index = start, RETURN_OK) ;
=======
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK) ;
>>>>>>> ef9d9dae428d70487b58b75ef98fc608600b6700
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
<<<<<<< HEAD
				return (tok_container->op_index = start, RETURN_OK) ;
=======
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK) ;
>>>>>>> ef9d9dae428d70487b58b75ef98fc608600b6700
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

t_error_status	find_external_parenthesis(t_ast_p *op, t_tok_container_p tok_container)
{
	t_token_p	cur_token;
	int			n = 0;
	
	if (*tok_container->tokens && (*tok_container->tokens)->type == T_LPARENT)
	{
		*op = ft_calloc(1, sizeof(t_ast));
		if (*op)
		{
			tok_container->op_index++;
			(*op)->type = OP_SUBSHELL;
<<<<<<< HEAD
			return (RETURN_OK) ;
=======
			return (free(*tok_container->tokens), *tok_container->tokens = NULL, RETURN_OK) ;
>>>>>>> ef9d9dae428d70487b58b75ef98fc608600b6700
		}
	}
	return (RETURN_FAIL);	
}

/* t_error_status	find_external_cntl_and_or(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
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
				return (tok_container->op_index = start, RETURN_OK) ;
			}
			else if (cur_token->type == T_OR && !in_parenthesis)
			{
				(*op)->type = OP_OR;
				return (tok_container->op_index = start, RETURN_OK) ;
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
				return (tok_container->op_index = start, RETURN_OK) ;
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

t_error_status	find_external_parenthesis(t_ast_p *op, t_tok_container_p tok_container)
{
	t_token_p	cur_token;
	int			n = 0;
	
	if (tok_container->tokens && (*tok_container->tokens)->type == T_LPARENT)
	{
		*op = ft_calloc(1, sizeof(t_ast));
		if (*op)
		{
			tok_container->op_index++;
			(*op)->type = OP_SUBSHELL;
			return (RETURN_OK) ;
		}
	}
	return (RETURN_FAIL);	
}
 */