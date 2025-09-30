/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cntl_pipe.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
<<<<<<< HEAD
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 15:16:29 by ihadj            ###   ########.fr       */
=======
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:01:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 19:55:45 by cgajean          ###   ########.fr       */
>>>>>>> origin/protect_facto_parse
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

int	parse_cntl_pipe(t_minishell_p shell, t_ast_p *op, t_build_var vars)
{
	t_token_p	cur_token;
	int			in_parenthesis;

	
	in_parenthesis = 0;
	cur_token = shell->tokens->tokens[vars.start];
	
	while (cur_token && vars.start <= vars.end)
	{
		if (cur_token->type == T_PIPE && !in_parenthesis)
		{
<<<<<<< HEAD
			cur_token = tok_container->tokens[start];
			if (cur_token->type == T_PIPE && !in_parenthesis)
			{
				(*op)->type = OP_PIPE;
				return (free(tok_container->tokens[start]), tok_container->tokens[start] = NULL, tok_container->op_index = start, RETURN_OK);
			}
			else if (cur_token->type == T_LPARENT)
				++in_parenthesis;
			else if (cur_token->type == T_RPARENT)
				--in_parenthesis;					
/* 			else if (cur_token->type == T_LPARENT && !in_parenthesis)
				in_parenthesis = 1;
			else if (cur_token->type == T_RPARENT && in_parenthesis)
				in_parenthesis = 0;		 */
			start++;
=======
			_create_cntl_pipe(shell, op, cur_token, vars.start);
			return (shell->abort == false);
>>>>>>> origin/protect_facto_parse
		}
		else if (cur_token->type == T_LPARENT)
			++in_parenthesis;
		else if (cur_token->type == T_RPARENT)
			--in_parenthesis;
		cur_token = shell->tokens->tokens[++vars.start];
	}
	return (RETURN_FAIL);
}
