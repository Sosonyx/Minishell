/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/30 11:12:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	_seek_cntl_op(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	if (NO_ABORT && parse_cntl_and_or(shell, ast, vars))
		return (RETURN_OK);
	else if (NO_ABORT && parse_cntl_pipe(shell, ast, vars))
		return (RETURN_OK);
	else if (NO_ABORT && parse_subshell(shell, ast, vars))
		return (RETURN_OK);
	else
		return (RETURN_FAIL);
}

static void	_recbuild(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	if (_seek_cntl_op(shell, ast, vars))
	{
		if (*ast && (*ast)->type != OP_SUBSHELL)
		{
			(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
			if ((*ast)->cntl_op)
			{
				vars.op_pos = shell->tokens->op_index;
				vars.left_end = set_left_end(vars.start, vars.op_pos, shell->tokens);
				if (vars.start <= vars.left_end)
					build_ast(shell, &(*ast)->cntl_op->left, (t_build_var) {vars.start, vars.left_end});
				vars.right_end = set_right_end(vars.op_pos, vars.end, shell->tokens, &vars.right_start);
				if (vars.right_start <= vars.right_end)
					build_ast(shell, &(*ast)->cntl_op->right, (t_build_var) {vars.right_start, vars.right_end});
			}
			else
				set_abort(shell, MEM_ERRMSG);
		}
	}
	else if (NO_ABORT)
		create_leaf(shell, ast, vars);
}

void	build_ast(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
		vars.end = set_global_end(vars, shell->tokens);
		_recbuild(shell, ast, vars);
}

static void	_init_ast(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	vars.end = init_global_end(vars, shell->tokens);
	_recbuild(shell, ast, vars);
}

int	parse_tokens(t_minishell_p shell, t_ast_p *ast)
{
	if (NO_ABORT)
	{
		_init_ast(shell, ast, (t_build_var) {0});
	}
	return (shell->abort == false);
}
