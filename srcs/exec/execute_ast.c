/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/16 19:40:26 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	_execute_ast(t_minishell_p shell, t_ast_p ast)
{
	int	rstatus;

	if (!ast)
		return (EXIT_FAILURE);
	if (ast->leaf)
		execute_leaf(shell, ast);
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
		print_generic_error(AST_ERRMSG);
		return (EXIT_FAILURE);
	}
	if (ast->leaf)
	{
		execute_leaf(shell, ast);
		waitpid(ast->leaf->pid, &rstatus, 0);
		return (rstatus);
	}
	else
		return (_execute_ast(shell, ast));
}
