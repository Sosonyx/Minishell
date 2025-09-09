/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 12:57:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_ast(t_minishell_p shell, t_ast_p ast);

int execute_cntl_and(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code;

	ret_code = exec_ast(shell, ast->cntl_op->left);
	ret_code = extract_return_code(&ret_code);
	if (!ret_code)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right);
		ret_code = extract_return_code(&ret_code);
	}
	return (ret_code);
}

int execute_cntl_or(t_minishell_p shell, t_ast_p ast)
{
	if (!exec_ast(shell, ast->cntl_op->left))
		exec_ast(shell, ast->cntl_op->right);
	
	return (0);		// temporaire
}

int execute_cntl_pipe(t_minishell_p shell, t_ast_p ast)
{
	exec_ast(shell, ast->cntl_op->left);
	exec_ast(shell, ast->cntl_op->right);

	return (0);		// temporaire
}

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	t_minishell_p	subshell;

	subshell = shell_init(shell->ac, shell->av, shell->environ);
	if (subshell)
	{
		subshell->subshell = true;
		exec_ast(subshell, ast->cntl_op->left);
		shell_destroy(subshell);
	}
	else
	{
		print_generic_error(MEM_ERRMSG);		
		// restart immediat ou laisser finir ce qui peut etre fini ?
	}

	return (0);		// temporaire
}

static int	exec_ast(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code;
	
	if (ast->leaf)
		return (execute_leaf(shell, ast));
	else
	{
		if (ast->type == OP_AND)
			ret_code = execute_cntl_and(shell, ast);
		else if (ast->type == OP_OR)
			ret_code = execute_cntl_or(shell, ast);
		else if (ast->type == OP_PIPE)
			ret_code = execute_cntl_pipe(shell, ast);
		else if (ast->type == OP_SUBSHELL)
			ret_code = execute_subshell(shell, ast);
	}
	return (ret_code);
}

int	execute_ast(t_minishell_p shell, t_ast_p ast)
{
	int	return_code;

	if (!ast)
		return (-1);
	return_code = exec_ast(shell, ast);
	return_code = extract_return_code(&return_code);
	return (return_code);
}
