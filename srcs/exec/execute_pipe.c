/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/11 17:14:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipe(t_ast_p ast)
{
	int	pipe_return;

	pipe_return = pipe(ast->pipefds);
	if (pipe_return == -1)
		return (print_generic_error(PIP_ERRMSG), -1);
	else
		return(0);
}

int execute_pipe(t_minishell_p shell, t_ast_p ast)
{
	t_leaf_p	cur_leaf;
	t_cntl_op_p	cur_cntl;
	
	/************************************************** */
	/* pipe */
		
	if (create_pipe(ast) == -1) return (-1);

	/************************************************** */
	/* left */
	
	cur_leaf = ast->cntl_op->left->leaf;
	if (cur_leaf)
	{
		preconfig_leaf(shell, cur_leaf);
		if (!ast->cntl_op->left->leaf->r_out)
		{
			if (ast->prev_pipefds)
				ast->cntl_op->left->leaf->pipefd[1] = ast->prev_pipefds[1];
			else
				ast->cntl_op->left->leaf->pipefd[1] = ast->pipefds[1];
		}
		else
			close(ast->pipefds[1]);		
	}
	else
	{
		ast->cntl_op->left->prev_pipefds = ast->pipefds;
	}



	
	/************************************************** */
	/* right */
	
	cur_leaf = ast->cntl_op->right->leaf;
	if (cur_leaf)
	{
		preconfig_leaf(shell, cur_leaf);
		if (!ast->cntl_op->right->leaf->r_in)
		{
			if (ast->prev_pipefds)
				ast->cntl_op->right->leaf->pipefd[0] = ast->prev_pipefds[0];
			else
				ast->cntl_op->right->leaf->pipefd[0] = ast->pipefds[0];
		}
		else
			close(ast->pipefds[0]);
	}
	else
	{
		ast->cntl_op->right->prev_pipefds = ast->pipefds;
	}
	execute_ast(shell, ast->cntl_op->left);
	close(ast->pipefds[1]);
	execute_ast(shell, ast->cntl_op->right);
	close(ast->pipefds[0]);
	
	return (0);		// temporaire
}

/* int execute_pipe(t_minishell_p shell, t_ast_p ast)
{
	if (pipe(ast->cntl_op->pipefds) == -1)
	{
		print_generic_error(PIP_ERRMSG);
		;	// que faire ?
	}
	else
	{
		preconfig_leaf(shell, ast->cntl_op->left->leaf);
		preconfig_leaf(shell, ast->cntl_op->right->leaf);
		if (!ast->cntl_op->left->leaf->r_out)
			ast->cntl_op->left->leaf->pipefd[1] = ast->cntl_op->pipefds[1];
		else
			close(ast->cntl_op->pipefds[1]);
		if (!ast->cntl_op->right->leaf->r_in)
			ast->cntl_op->right->leaf->pipefd[0] = ast->cntl_op->pipefds[0];
		else
			close(ast->cntl_op->pipefds[0]);
	}
	execute_ast(shell, ast->cntl_op->left);
	close(ast->cntl_op->pipefds[1]);
	execute_ast(shell, ast->cntl_op->right);
	close(ast->cntl_op->pipefds[0]);
	
	return (0);		// temporaire
} */
