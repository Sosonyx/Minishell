/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/17 13:59:25 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_execute_ast(t_shell_p shell, t_ast_p ast)
{
	if (ast->leaf)
		execute_leaf(shell, ast);
	else
	{
		if (ast->type == OP_AND)
			execute_and(shell, ast);
		else if (ast->type == OP_OR)
			execute_or(shell, ast);
		else if (ast->type == OP_PIPE)
			execute_pipe(shell, ast);
		else if (ast->type == OP_SUBSHELL)
			execute_subshell(shell, ast);
	}
}

void	execute_ast(t_shell_p shell, t_ast_p *ast)
{
	signals_setter_exec();
	if (!*ast)
	{
		print_generic_error(shell, AST_ERRMSG);
		shell->exit_code = ERRVAL1;
	}
	if ((*ast)->leaf)
	{
		execute_leaf(shell, *ast);
		if (!(*ast)->leaf->is_heredoc && (*ast)->leaf->pid > 0)
			waitpid((*ast)->leaf->pid, &shell->exit_code, 0);
	}
	else
	{
		_execute_ast(shell, *ast);
	}
	handle_signal_error(shell);
	signals_setter();
}
