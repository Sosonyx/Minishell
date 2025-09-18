/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 12:59:00 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_execute_ast(t_minishell_p shell, t_ast_p ast)
{
	int	rstatus;

	if (!ast)
		return (EXIT_FAILURE);
	if (ast->leaf)
		rstatus = execute_leaf(shell, ast);
	else
	{
		if (ast->type == OP_AND)
			rstatus = execute_and(shell, ast);
		else if (ast->type == OP_OR)
			rstatus = execute_or(shell, ast);
		else if (ast->type == OP_PIPE)
			rstatus = execute_pipe(shell, ast);
		else if (ast->type == OP_SUBSHELL)
			rstatus = execute_subshell(shell, ast);
	}
	return (rstatus);
}

int	execute_ast(t_minishell_p shell, t_ast_p ast)
{
	int	rstatus;

	if (!ast)
	{
		print_generic_error(shell, AST_ERRMSG);
		return (EXIT_FAILURE);
	}
	if (ast->leaf)
	{
		rstatus = execute_leaf(shell, ast);
		waitpid(ast->leaf->pid, &rstatus, 0);
	}
	else
	{
		rstatus = _execute_ast(shell, ast);
	}
	destroy_ast(&ast);
	return (rstatus);
}
