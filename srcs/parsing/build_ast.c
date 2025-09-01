/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/01 15:08:34 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// j ai lexee (tokeniser), ensuite j ai check les erreurs de syntax, 
// mtn je dois parser pour definir si les element sont des REDIR-IN etc ...

/* static void	create_node(t_ast_p ast, t_token_p token)
{
	if (token->type == T_WORD)
		;		
	else if (token->type == T_PIPE)
		;
	else if (token->type == T_REDIR_IN)
		;
	else if (token->type == T_REDIR_OUT)
		;
	else if (token->type == T_APPEND)
		;
	else if (token->type == T_HEREDOC)
		;
	else if (token->type == T_AND)
		;
	else if (token->type == T_OR)
		;
	else if (token->type == T_LPARENT)	
		;
	else if (token->type == T_RPARENT)	
		;
	else if (token->type == T_EXPAND)	
		;
} */

void	reach_target_token(t_arg_p **tokens, int *index)
{
	int			n = 0;
	
	while (**tokens && n < *index)
		(*tokens)++;
}

t_sub_ast_p	find_external_cntl_and_or(t_arg_p *tokens, int *index)
{
	t_token_p	cur_token;
	t_sub_ast_p	new_op;
		
	*index = 0;	
	new_op = ft_calloc(1, sizeof(t_sub_ast));
	if (new_op)
	{
		reach_target_token(&tokens, index);
		while (*tokens)
		{
			cur_token = *tokens;
			if (ft_strcmp(cur_token->val, "&&"))
			{
				new_op->type == OP_AND;
				break ;
			}
			else if (ft_strcmp(cur_token->val, "||"))
			{
				new_op->type == OP_OR;
				break ;
			}
			tokens++;
			(*index++);
		}
		free(new_op);
		new_op = NULL;
	}
	return (new_op);
}

t_sub_ast_p	find_external_cntl_pipe(t_arg_p *tokens, int *index)
{
	t_token_p	cur_token;
	t_sub_ast_p	new_op;
	int			n = 0;
	
	*index = 0;	
	new_op = ft_calloc(1, sizeof(t_sub_ast));
	if (new_op)
	{
		reach_target_token(&tokens, index);
			
		while (*tokens)
		{
			cur_token = *tokens;
			if (ft_strcmp(cur_token->val, "|"))
			{
				new_op->type == OP_PIPE;
				break ;
			}
			tokens++;
			(*index++);
		}
		free(new_op);
		new_op = NULL;
	}
	return (new_op);
}

static void	parse_tokens(t_ast_p ast, t_arg_p tok_container, int *index_value)
{
	bool		parenthesis = 0;
	int			index = 0, *index_ptr;
	t_sub_ast_p	current_op;

	if (index_value)
		index_ptr = index_value;
	else
		index_ptr = &index;
		
	current_op = find_external_cntl_and_or(tok_container, index_ptr);
	if (!current_op)
	{		*index_ptr = 0;
		current_op = find_external_cntl_pipe(tok_container, index_ptr);
		if (!current_op)
		{
			current_op = ft_calloc(1, sizeof(t_sub_ast));
			if (current_op)
			{
				;					// it's a leaf
				return ;
			}
		}
	}
	parse_tokens(current_op, tok_container, index_ptr);
}

t_error_status	build_ast(t_ast_p ast, t_arg_p tok_container)
{
	ast = ft_calloc(1, sizeof(t_ast));
	if (ast)
	{
		parse_tokens(ast, tok_container, NULL);
	}
	else
	{
		return (free(tok_container), RETURN_FAIL);
	}
	return (RETURN_OK);
}
