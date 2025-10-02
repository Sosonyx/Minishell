/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/02 18:17:22 by ihadj            ###   ########.fr       */
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
		shell->exit_code = EXIT_FAILURE;
	}
	if (NO_ABORT && (*ast)->leaf)
	{
		execute_leaf(shell, *ast);
		if ((*ast)->leaf->pid)
		{
			waitpid((*ast)->leaf->pid, &shell->exit_code, 0);
			if (shell->exit_code == SIGINT)
				printf("\n");
			else if (shell->exit_code == SIGQUIT + 128)
				printf("Quit (core dumped)\n");
		}
		signals_setter();
	}
	else if (NO_ABORT)
	{
		_execute_ast(shell, *ast);
	}
	destroy_ast(ast);
}
