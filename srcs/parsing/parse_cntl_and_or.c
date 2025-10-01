/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cntl_and_or.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:55 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/01 17:18:05 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_create_cntl_and_or(t_minishell_p shell, t_ast_p *op, t_token_p cur_token, int n)
{
	if (create_cntl_op(shell, op, cur_token->type))
	{
		free(shell->tokens->tokens[n]);
		shell->tokens->tokens[n] = NULL;
		shell->tokens->op_index = n;
		discard_token(shell, n);
	}
}

int	parse_cntl_and_or(t_minishell_p shell, t_ast_p *op, t_build_var vars)
{
	t_token_p			cur_token;
	int					in_parenthesis;
	t_tok_container_p	tok_copy;

	tok_copy = shell->tokens;
	in_parenthesis = 0;
	cur_token = shell->tokens->tokens[vars.start];
	while (cur_token && vars.start <= vars.end)
	{
		if ((cur_token->type & (T_AND | T_OR)) && !in_parenthesis)
		{
			_create_cntl_and_or(shell, op, cur_token, vars.start);
			return (shell->abort == false);
		}
		else if (cur_token->type == T_LPARENT)
			++in_parenthesis;
		else if (cur_token->type == T_RPARENT)
			--in_parenthesis;
		cur_token = shell->tokens->tokens[++vars.start];
	}
	return (RETURN_FAIL);
}
