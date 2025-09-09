/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 16:41:32 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_ast(t_minishell_p shell, t_ast_p ast, bool pipe_case);

int execute_cntl_and(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code = 0;

	if (ast->cntl_op->left)
	{
		ret_code = exec_ast(shell, ast->cntl_op->left, false);
		ret_code = extract_return_code(&ret_code);
	}
	if (!ret_code && ast->cntl_op->right)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right, false);
		ret_code = extract_return_code(&ret_code);
	}
	return (ret_code);
}

int execute_cntl_or(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code;

	ret_code = exec_ast(shell, ast->cntl_op->left, false);
	ret_code = extract_return_code(&ret_code);
	if (ret_code)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right, false);
		ret_code = extract_return_code(&ret_code);
	}
	else if (!ret_code && (ast->cntl_op->right->type == OP_AND \
		|| ast->cntl_op->right->type == OP_OR))
	{
		ret_code = exec_ast(shell, ast->cntl_op->right->cntl_op->right, false);
		ret_code = extract_return_code(&ret_code);
	}
	else if (!ret_code && ast->cntl_op->right->type == OP_PIPE)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right, true);
		ret_code = extract_return_code(&ret_code);		
	}
	return (ret_code);
}

int execute_cntl_pipe(t_minishell_p shell, t_ast_p ast)
{
	pipe(ast->leaf->pipefds);
	exec_ast(shell, ast->cntl_op->left, true);
	exec_ast(shell, ast->cntl_op->right, true);
	return (0);		// temporaire
}

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	t_minishell_p	subshell;

	subshell = shell_init(shell->ac, shell->av, shell->environ);
	if (subshell)
	{
		subshell->subshell = true;
		exec_ast(subshell, ast->cntl_op->left, false);
		shell_destroy(subshell);
	}
	else
	{
		print_generic_error(MEM_ERRMSG);
		// restart immediat ou laisser finir ce qui peut etre fini ?
	}

	return (0);		// temporaire
}

static int	exec_ast(t_minishell_p shell, t_ast_p ast, bool pipe_case)
{
	int	ret_code;
	
	if (ast->leaf)
		return (execute_leaf(shell, ast, pipe_case));
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
	return_code = exec_ast(shell, ast, false);
	return (return_code);
}
