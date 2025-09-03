/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/03 12:41:06 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_p build_redir(t_tok_container_p tok_container, int i)
{
	return (NULL);
}

t_error_status	create_leaf(t_ast_p ast, t_tok_container_p tok_container, int index_value)
{
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
	else if (branch == RIGHT_BRANCH && !first)
		end_index = end;
	if (first)
		*ast = ft_calloc(1, sizeof(struct s_ast));
	else
	{
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
	}
	if (ast)
	{
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
}

t_error_status		parse_tokens(t_ast_p *ast, t_tok_container_p tok_container)
{
	if (ast)
		build_ast(ast, tok_container, 0, 0, AST_INIT, 1);
	if (*ast)
		return (RETURN_OK);
	else
		return (RETURN_FAIL);
}
