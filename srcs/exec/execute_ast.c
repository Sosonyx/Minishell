/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/26 11:02:06 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_execute_ast(t_minishell_p shell, t_ast_p ast)
{
	if (!ast)
		return (EXIT_FAILURE);
	if (ast->leaf)
		shell->last_status = execute_leaf(shell, ast);
	else
	{
		if (ast->type == OP_AND)
			shell->last_status = execute_and(shell, ast);
		else if (ast->type == OP_OR)
			shell->last_status = execute_or(shell, ast);
		else if (ast->type == OP_PIPE)
			shell->last_status = execute_pipe(shell, ast);
		else if (ast->type == OP_SUBSHELL)
			shell->last_status = execute_subshell(shell, ast);
	}
	return (shell->last_status);
}

int	execute_ast(t_minishell_p shell, t_ast_p *ast)
{
	if (!*ast)
	{
		print_generic_error(shell, AST_ERRMSG);
		return (EXIT_FAILURE);
	}
	if ((*ast)->leaf)
	{
		shell->last_status = execute_leaf(shell, *ast);
		waitpid((*ast)->leaf->pid, &shell->last_status, 0);
	}
	else
	{
		shell->last_status = _execute_ast(shell, *ast);
	}
	destroy_ast(ast);
	return (shell->last_status);
}
