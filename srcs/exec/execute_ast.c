/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/11 17:03:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_ast(t_minishell_p shell, t_ast_p ast)
{
	int	return_code;

	if (!ast)
		return (EXIT_FAILURE);
	if (ast->leaf)
		return_code = execute_leaf(shell, ast);
	else
	{
		if (ast->type == OP_AND)
			return_code = execute_and(shell, ast);
		else if (ast->type == OP_OR)
			return_code = execute_or(shell, ast);
		else if (ast->type == OP_PIPE)
			return_code = execute_pipe(shell, ast);
		else if (ast->type == OP_SUBSHELL)
			return_code = execute_subshell(shell, ast);
	}
	return_code = extract_return_code(return_code);
	return (return_code);
}
