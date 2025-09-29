/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 19:30:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_subshell_limit(t_minishell_p shell, int start, int *end)
{
	while (*end >= 0 && *end > start)
	{
		if ((!shell->tokens->tokens[*end]))
			(*end)--;
		else if ((shell->tokens->tokens[*end]->type != T_RPARENT))
			(*end)--;
		else
			break ;
	}
}

static void	_parse_subshell(t_minishell_p shell, t_ast_p *op, struct s_build_var vars)
{
	if (create_cntl_op(shell, op, T_LPARENT))
	{
		discard_token(shell, vars.start);
		discard_token(shell, vars.end);
		(*op)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
		if ((*op)->cntl_op)
		{
			++vars.start;
			--vars.end;
			_build_ast(shell, &(*op)->cntl_op->left, vars, LEFT_BRANCH);
		}
		else
		{
			set_abort(shell, MEM_ERRMSG);
			free(*op);
		}
	}
	else
		set_abort(shell, MEM_ERRMSG);
}

int	parse_subshell(t_minishell_p shell, t_ast_p *op, struct s_build_var vars)
{
	if (shell->tokens->tokens[vars.start] && (shell->tokens->tokens[vars.start])->type == T_LPARENT)
	{
		get_subshell_limit(shell, vars.start, &vars.end);
		_parse_subshell(shell, op, vars);
		return (shell->abort == false);
	}
	else
		return (RETURN_FAIL);
	
}
