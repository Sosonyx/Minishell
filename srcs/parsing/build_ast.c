/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/01 18:14:05 by cgajean          ###   ########.fr       */
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

/* static void	build_redir(t_tok_container_p tok_container, int index)
{
	int	i;
	

	i = 0;
	
	while (tok_container->tokens[i])
	{
		if (is_redir(tok_container->tokens[i]))
			
	}
}

static void	create_leaf(t_leaf_p leaf, t_tok_container_p tok_container, int index_value)
{
	leaf->cmds = ;
	leaf->redir = build_redir();
	leaf->is_builtin = ;
} */

void	reach_target_token(t_tok_container_p *tokens, int *index)
{
	int			n = 0;
	
	while (*tokens && n <= *index)
		(*tokens)++;
}

t_sub_ast_p	find_external_cntl_and_or(t_tok_container_p tok_container, int *index)
{
	t_token_p	cur_token;
	t_sub_ast_p	new_op;
		
	*index = 0;	
	new_op = ft_calloc(1, sizeof(t_sub_ast));
	if (new_op)
	{
		reach_target_token(&tok_container, index);
		while (tok_container->tokens)
		{
			cur_token = tok_container->tokens;
			if (cur_token->type == T_AND)
			{
				new_op->type == OP_AND;
				break ;
			}
			else if (cur_token->type == T_OR)
			{
				new_op->type == OP_OR;
				break ;
			}
			tok_container++;
			(*index++);
		}
		free(new_op);
		new_op = NULL;
	}
	return (new_op);
}

t_sub_ast_p	find_external_cntl_pipe(t_tok_container_p tok_container, int *index)
{
	t_token_p	cur_token;
	t_sub_ast_p	new_op;
	int			n = 0;
	
	*index = 0;	
	new_op = ft_calloc(1, sizeof(t_sub_ast));
	if (new_op)
	{
		reach_target_token(&tok_container, index);
			
		while (tok_container->tokens)
		{
			cur_token = tok_container->tokens;
			if (cur_token->type == T_PIPE)
			{
				new_op->type == OP_PIPE;
				break ;
			}
			tok_container++;
			(*index++);
		}
		free(new_op);
		new_op = NULL;
	}
	return (new_op);
}

static void	parse_tokens(t_ast_p ast, t_tok_container_p tok_container, int *index_value)
{
	int			index = 0;
	int			*index_ptr;
	int			start;
	t_sub_ast_p	current_op;

	if (index_value)
		index_ptr = index_value;
	else
		index_ptr = &index;
	start = *index_ptr;
	
	current_op = find_external_cntl_and_or(tok_container, index_ptr);
	if (!current_op)
	{
		current_op = find_external_cntl_pipe(tok_container, index_ptr);
		if (!current_op)
		{
			current_op = ft_calloc(1, sizeof(t_sub_ast));
			if (current_op)
			{
				create_leaf(&ast->leaf, tok_container, index_ptr);				// it's a leaf
				return ;
			}
		}
	}
	ast->cntl_op = current_op;
	parse_tokens(current_op->cntl_op->left, tok_container, start);				// le prototype de la fonction n'est pas comme ca
	parse_tokens(current_op->cntl_op->right, tok_container, *index_ptr + 1);	// les pointeurs sur int ne fonctionnent pas
}

t_ast_p	build_ast(t_ast_p ast, t_tok_container_p tok_container)
{
	ast = ft_calloc(1, sizeof(t_ast));
	if (ast)
	{
		parse_tokens(ast, tok_container, NULL);
	}
	return (ast);
}
