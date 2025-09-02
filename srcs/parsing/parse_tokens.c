/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/02 12:24:56 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	build_redir(t_tok_container_p tok_container, int index)
{
	return ;
/* 	int	i;
	

	i = 0;
	
	while (tok_container->tokens[i])
	{
		if (is_redir(tok_container->tokens[i]))
			
	} */
}

t_error_status	create_leaf(t_sub_ast_p *op, t_tok_container_p tok_container, int index_value)
{
/* 	leaf->cmds =;
	leaf->redir = build_redir();
	leaf->is_builtin =;
*/
	return (RETURN_OK);
}

/* void	reach_target_token(t_tok_container_p *tokens, int start)
{
	int			n = 0;
	
	while ((*tokens)->tokens && n < start)
	{
		(*tokens)->tokens++;
		n++;
	}
} */

t_error_status	find_external_cntl_and_or(t_sub_ast_p *op, t_tok_container_p tok_container, int start)
{
	t_token_p			cur_token;
	int					in_parenthesis = 0;
	t_tok_container_p	tok_copy = tok_container;
	
	*op = ft_calloc(1, sizeof(t_sub_ast));
	if (*op)
	{
		while (tok_container->tokens[start])
		{
			cur_token = tok_container->tokens[start++];
			printf("%s\n", cur_token->val);
			if (cur_token->type == T_AND && !in_parenthesis)
			{
				(*op)->type = OP_AND;
				return (tok_container->cur_index = start, RETURN_OK) ;
			}
			else if (cur_token->type == T_OR && !in_parenthesis)
			{
				(*op)->type = OP_OR;
				return (tok_container->cur_index = start, RETURN_OK) ;
			}
			else if (cur_token->type == T_LPARENT && !in_parenthesis)
				in_parenthesis = 1;
			else if (cur_token->type == T_RPARENT && in_parenthesis)
				in_parenthesis = 0;
		}
		free(*op);
		*op = NULL;
	}
	return (RETURN_FAIL);
}

t_error_status	find_external_cntl_pipe(t_sub_ast_p *op, t_tok_container_p tok_container, int start)
{
	t_token_p	cur_token;
	int			n = 0;
	int			in_parenthesis = 0;
	
	*op = ft_calloc(1, sizeof(t_sub_ast));
	if (*op)
	{
		while (tok_container->tokens[start])
		{
			cur_token = tok_container->tokens[start++];
			printf("%s\n", cur_token->val);
			if (cur_token->type == T_PIPE && !in_parenthesis)
			{
				(*op)->type = OP_PIPE;
				return (tok_container->cur_index = start, RETURN_OK) ;
			}
			else if (cur_token->type == T_LPARENT && !in_parenthesis)
				in_parenthesis = 1;
			else if (cur_token->type == T_RPARENT && in_parenthesis)
				in_parenthesis = 0;			
		}
		free(*op);
		*op = NULL;
	}
	return (RETURN_FAIL);
}

t_error_status	find_external_parenthesis(t_sub_ast_p *op, t_tok_container_p tok_container)
{
	t_token_p	cur_token;
	int			n = 0;
	
	if ((*tok_container->tokens)->type == T_LPARENT)
	{
		*op = ft_calloc(1, sizeof(t_sub_ast));
		if (*op)
		{
			tok_container->cur_index++;
			(*op)->type = OP_SUBSHELL;
			return (RETURN_OK) ;
		}
	}
	return (RETURN_FAIL);	
}

static void	build_ast(t_ast_p ast, t_tok_container_p tok_container, t_ast_branch branch)
{
	int			start;
	
	if (branch == LEFT_BRANCH)
		start = tok_container->start_index;
	else if (branch == RIGHT_BRANCH)
		start = tok_container->cur_index;
	else
		start = 0;

	if (!find_external_cntl_and_or(&ast, tok_container, start))
	{
		if (!find_external_cntl_pipe(&ast, tok_container, start))
		{
			if (!find_external_parenthesis(&ast, tok_container))
			{
				if (!create_leaf(&ast, tok_container, start))
					; // kill_shell();
				else
					return ;
			}
		}
	}
	ast->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
	if (ast->cntl_op)
	{
		tok_container->start_index = start;
		// build_ast(ast->cntl_op->left, tok_container, LEFT_BRANCH);
		build_ast(ast->cntl_op->right, tok_container, RIGHT_BRANCH);
	}
	else
		;	// kill_shell();
}

t_ast_p	parse_tokens(t_ast_p ast, t_tok_container_p tok_container)
{
	build_ast(ast, tok_container, AST_INIT);
	return (ast);
}
