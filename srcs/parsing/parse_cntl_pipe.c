/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cntl_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 16:56:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_create_cntl_pipe(t_minishell_p shell, t_ast_p *op, t_token_p cur_token, int n)
{
	if (create_cntl_op(shell, op, cur_token->type))
	{
		free(shell->tokens->tokens[n]);
		shell->tokens->tokens[n] = NULL;
		shell->tokens->op_index = n;
		discard_token(shell, n);
	}
	else
		set_abort(shell, MEM_ERRMSG);
}

int	parse_cntl_pipe(t_minishell_p shell, t_ast_p *op, int start, int end)
{
	t_token_p	cur_token;
	int			in_parenthesis;

	in_parenthesis = 0;
	cur_token = shell->tokens->tokens[start];
	
	while (cur_token && start <= end)
	{
		if (cur_token->type == T_PIPE && !in_parenthesis)
		{
			_create_cntl_pipe(shell, op, cur_token, start);
			return (shell->abort == false);
		}
		else if (cur_token->type == T_LPARENT)
			++in_parenthesis;
		else if (cur_token->type == T_RPARENT)
			--in_parenthesis;
		cur_token = shell->tokens->tokens[++start];
	}
	return (RETURN_FAIL);
}
