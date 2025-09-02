/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/02 16:03:24 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_p build_redir(t_tok_container_p tok_container, int i)
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

t_error_status	create_leaf(t_ast_p ast, t_tok_container_p tok_container, int index_value)
{
	// leaf->cmds =;
	build_redir(tok_container, index_value);
	// leaf->is_builtin =;

	return (RETURN_OK);
}

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

static void	build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, int branch, int first)
{
	int	subshell = 0;
	
	while (tok_container->tokens && tok_container->tokens[end])
		end++;
	if (branch == 0 && first != 1)
	{
		if (!find_external_cntl_and_or(ast, tok_container, start, tok_container->op_index - 1))
		{
			if (!find_external_cntl_pipe(ast, tok_container, start, tok_container->op_index - 1))
			{
				if (!find_external_parenthesis(ast, tok_container))
				{
					if (!create_leaf(*ast, tok_container, start))
						; // kill_shell();
					else
					{
						if (!first)
							return ;
					}
						
				}
				else
					subshell = 1;
			}
		}
	}
	else
		if (!find_external_cntl_and_or(ast, tok_container, start, end))
		{
			if (!find_external_cntl_pipe(ast, tok_container, start, end))
			{
				if (!find_external_parenthesis(ast, tok_container))
				{
					if (!create_leaf(*ast, tok_container, start))
						; // kill_shell();
					else
						return ;
				}
				else
					subshell = 1;
			}
		}
	(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
	if ((*ast)->cntl_op)
	{
		build_ast(&(*ast)->cntl_op->left, tok_container, start, tok_container->op_index - 1, 0, 0);
		if (!subshell)
			build_ast(&(*ast)->cntl_op->right, tok_container, tok_container->op_index + 1, end, 1, 0);
	}
	else
		;	// kill_shell();
}

t_ast_p		parse_tokens(t_ast_p ast, t_tok_container_p tok_container)
{
	if (ast)
		build_ast(&ast, tok_container, 0, 0, 0, 1);
	return (ast);
}
