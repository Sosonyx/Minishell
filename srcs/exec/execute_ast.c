/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/14 15:31:19 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_minishell_p shell, t_ast_p ast)
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
	return (extract_return_code(rstatus));
}
