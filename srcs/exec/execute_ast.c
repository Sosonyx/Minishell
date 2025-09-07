/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/07 14:03:31 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_return_status	parse_and_execute(t_minishell_p shell, t_ast_p ast);

void execute_cntl_and(t_minishell_p shell, t_ast_p ast)
{
	if (parse_and_execute(shell, ast->cntl_op->left))
		parse_and_execute(shell, ast->cntl_op->right);
}

void execute_cntl_or(t_minishell_p shell, t_ast_p ast)
{
	if (!parse_and_execute(shell, ast->cntl_op->left))
		parse_and_execute(shell, ast->cntl_op->right);
}

void execute_cntl_pipe(t_minishell_p shell, t_ast_p ast)
{
	parse_and_execute(shell, ast->cntl_op->left);
	parse_and_execute(shell, ast->cntl_op->right);
}

void execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	parse_and_execute(shell, ast->cntl_op->left);
}

static t_return_status	parse_and_execute(t_minishell_p shell, t_ast_p ast)
{
	if (ast->leaf)
		return (execute_leaf(shell, ast));
	else
	{
		if (ast->type == OP_AND)
			execute_cntl_and(shell, ast);
		else if (ast->type == OP_OR)
			execute_cntl_or(shell, ast);
		else if (ast->type == OP_PIPE)
			execute_cntl_pipe(shell, ast);
		else if (ast->type == OP_SUBSHELL)
			execute_subshell(shell, ast);
	}
	return (RETURN_OK);
}

int	execute_ast(t_minishell_p shell, t_ast_p ast)
{
	int	return_code;

	if (!ast)
		return (-1);
	parse_and_execute(shell, ast);
	return_code = wait_children(shell);
	return (return_code);
}
