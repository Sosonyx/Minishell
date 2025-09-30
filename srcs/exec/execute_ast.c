/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/30 19:47:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execute_ast(t_minishell_p shell, t_ast_p ast)
{
	if (NO_ABORT && ast->leaf)
		execute_leaf(shell, ast);
	else
	{
		if (NO_ABORT && ast->type == OP_AND)
			execute_and(shell, ast);
		else if (NO_ABORT && ast->type == OP_OR)
			execute_or(shell, ast);
		else if (NO_ABORT && ast->type == OP_PIPE)
			execute_pipe(shell, ast);
		else if (NO_ABORT && ast->type == OP_SUBSHELL)
			execute_subshell(shell, ast);
	}
}

void	execute_ast(t_minishell_p shell, t_ast_p *ast)
{
	if (!*ast)
	{
		print_generic_error(shell, AST_ERRMSG);
		shell->last_status = EXIT_FAILURE;
	}
	if (NO_ABORT && (*ast)->leaf)
	{
		execute_leaf(shell, *ast);
		waitpid((*ast)->leaf->pid, &shell->last_status, 0);
	}
	else if (NO_ABORT)
	{
		_execute_ast(shell, *ast);
	}
	destroy_ast(ast);
}
