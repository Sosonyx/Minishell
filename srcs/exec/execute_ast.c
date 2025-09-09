/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:54:51 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 19:54:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_ast(t_minishell_p shell, t_ast_p ast);

int execute_and(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code = 0;

	if (ast->cntl_op->left)
	{
		ret_code = exec_ast(shell, ast->cntl_op->left);
		ret_code = extract_return_code(&ret_code);
	}
	if (!ret_code && ast->cntl_op->right)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right);
		ret_code = extract_return_code(&ret_code);
	}
	return (ret_code);
}

int execute_or(t_minishell_p shell, t_ast_p ast)
{
	int	ret_code;

	ret_code = exec_ast(shell, ast->cntl_op->left);
	ret_code = extract_return_code(&ret_code);
	if (ret_code)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right);
		ret_code = extract_return_code(&ret_code);
	}
	else if (!ret_code && (ast->cntl_op->right->type == OP_AND \
		|| ast->cntl_op->right->type == OP_OR))
	{
		ret_code = exec_ast(shell, ast->cntl_op->right->cntl_op->right);
		ret_code = extract_return_code(&ret_code);
	}
	else if (!ret_code && ast->cntl_op->right->type == OP_PIPE)
	{
		ret_code = exec_ast(shell, ast->cntl_op->right);
		ret_code = extract_return_code(&ret_code);		
	}
	return (ret_code);
}

int execute_pipe(t_minishell_p shell, t_ast_p ast)
{
	if (pipe(ast->cntl_op->pipefds) == -1)
	{
		print_generic_error(PIP_ERRMSG);
		;	// que faire ?
	}
	else
	{
		get_redirections(ast->cntl_op->left->leaf);
		get_redirections(ast->cntl_op->right->leaf);
		if (!ast->cntl_op->left->leaf->r_out)
			ast->cntl_op->left->leaf->pipefd[1] = ast->cntl_op->pipefds[1];
		if (!ast->cntl_op->right->leaf->r_in)
			ast->cntl_op->right->leaf->pipefd[0] = ast->cntl_op->pipefds[0];
	}
	exec_ast(shell, ast->cntl_op->left);
	close(ast->cntl_op->pipefds[1]);	
	exec_ast(shell, ast->cntl_op->right);
	close(ast->cntl_op->pipefds[0]);
	
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
			ret_code = execute_and(shell, ast);
		else if (ast->type == OP_OR)
			ret_code = execute_or(shell, ast);
		else if (ast->type == OP_PIPE)
			ret_code = execute_pipe(shell, ast);
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
	return (return_code);
}

