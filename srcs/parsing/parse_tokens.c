/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/04 10:37:21 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	look_forward_next_token(t_tok_container_p tok_container, int start, int end)
{
	while (start <= end)
	{
		if (tok_container->tokens[start])
			break;
		start++;
	}
	return (start);
}

static int	set_end(t_tok_container_p tok_container, int *end, t_ast_branch branch, int first)
{
	while (tok_container->tokens && tok_container->tokens[*end])
		(*end)++;

	if (branch == LEFT_BRANCH && !first)
		return (tok_container->op_index - 1);
	else
		return (*end);
}

void	build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, t_ast_branch branch, int first)
{
    int subshell = 0;
    int end_index;
    int last;
	
	end_index = set_end(tok_container, &end, branch, first);
		
	if (!find_external_cntl_and_or(ast, tok_container, start, end_index))
	{
		if (!find_external_cntl_pipe(ast, tok_container, start, end_index))
		{
			if (!find_external_parenthesis(ast, tok_container, start, end))
			{
				if (!create_leaf(ast, tok_container, start))
					; // kill_shell();
				else
					return ;
			}
			else
				subshell = 1;
		}
	}
	if (!subshell && *ast)
	{
		(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
		if ((*ast)->cntl_op)
		{
			if (!subshell)
				build_ast(&(*ast)->cntl_op->left, tok_container, start, tok_container->op_index - 1, LEFT_BRANCH, 0);			
			build_ast(&(*ast)->cntl_op->right, tok_container, tok_container->op_index + 1, end, RIGHT_BRANCH, 0);
		}
		else
			;	// kill_shell();
	}
	start = look_forward_next_token(tok_container, start, end_index);
	if (start < end_index)
		build_ast(&(*ast)->cntl_op->right, tok_container, start, end, RIGHT_BRANCH, 0);
}

t_error_status		parse_tokens(t_ast_p *ast, t_tok_container_p tok_container)
{
	if (ast)
	{
		build_ast(ast, tok_container, 0, 0, AST_INIT, 1);

		if (*ast)
			return (RETURN_OK);
	}
	return (RETURN_FAIL);
}

