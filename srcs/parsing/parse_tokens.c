/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/03 14:44:57 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_status	create_leaf(t_ast_p *ast, t_tok_container_p tok_container, int i)
{
	*ast = ft_calloc(1, sizeof(t_ast));
	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
	if (!(*ast)->leaf)
		return (RETURN_FAIL);
	(*ast)->leaf->redir = build_redir(tok_container, i);
		
	build_cmd((*ast)->leaf->cmds, tok_container, i);
	// leaf->is_builtin =;

	return (RETURN_OK);
}

static void	build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, t_ast_branch branch, int first)
{
	int	subshell = 0;
	int	end_index;
	
	while (tok_container->tokens && tok_container->tokens[end])
		end++;

	if (branch == LEFT_BRANCH && !first)
		end_index = tok_container->op_index - 1;
	else
		end_index = end;
		
	if (!find_external_cntl_and_or(ast, tok_container, start, end_index))
	{
		if (!find_external_cntl_pipe(ast, tok_container, start, end_index))
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

	if (*ast)
	{
		(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
		if ((*ast)->cntl_op)
		{
			build_ast(&(*ast)->cntl_op->left, tok_container, start, tok_container->op_index - 1, LEFT_BRANCH, 0);
			if (!subshell)
				build_ast(&(*ast)->cntl_op->right, tok_container, tok_container->op_index + 1, end, RIGHT_BRANCH, 0);
		}
		else
			;	// kill_shell();
	}
}

t_error_status		parse_tokens(t_ast_p *ast, t_tok_container_p tok_container)
{
	if (ast)
	{
		// *ast = ft_calloc(1, sizeof(struct s_ast));
		// if (*ast)
		build_ast(ast, tok_container, 0, 0, AST_INIT, 1);
		if (*ast)
			return (RETURN_OK);
	}
	return (RETURN_FAIL);
}
