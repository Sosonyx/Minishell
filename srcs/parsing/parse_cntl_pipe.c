/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cntl_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/13 17:59:03 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_create_cntl_pipe(t_shell_p shell, t_ast_p *op, t_token_p cur_token, int n)
{
	create_cntl_op(shell, op, cur_token->type);
	shell->tokens->op_index = n;
	discard_token(shell, n);
}

int	parse_cntl_pipe(t_shell_p shell, t_ast_p *op, t_build_var vars)
{
	t_token_p	cur_token;
	int			in_parenthesis;

	in_parenthesis = 0;
	cur_token = shell->tokens->tokens[vars.start];
	while (cur_token && vars.start <= vars.end)
	{
		if (cur_token->type == T_PIPE && !in_parenthesis)
		{
			_create_cntl_pipe(shell, op, cur_token, vars.start);
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
