/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/12 15:02:30 by cgajean          ###   ########.fr       */
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
		int	test_flag = 0;
		
		preconfig_leaf(shell, cur_leaf);
		if (!ast->cntl_op->left->leaf->r_out)
		{
			if (ast->prev_pipefds && ast->prev_pipefds[1] > 2)
				ast->cntl_op->left->leaf->pipefd[1] = ast->prev_pipefds[1];
			else
				ast->cntl_op->left->leaf->pipefd[1] = ast->pipefds[1];
		}
		else
		{
			close(ast->pipefds[1]);
		}
		if (ast->prev_pipefds && ast->prev_pipefds[0] > 2)
		{
			ast->cntl_op->left->leaf->pipefd[0] = ast->prev_pipefds[0];
			test_flag = 1;
		}		
		execute_ast(shell, ast->cntl_op->left);
		if (test_flag)
		{
			close(ast->prev_pipefds[0]);
			ast->prev_pipefds[0] = -2;
		}	
	}
	else
	{
		ast->cntl_op->left->prev_pipefds = ast->pipefds;
		execute_ast(shell, ast->cntl_op->left);
	}

	// execute_ast(shell, ast->cntl_op->left);
	
	close(ast->pipefds[1]);
	ast->pipefds[1] = -2;
	
	/************************************************** */
	/* right */
	
	cur_leaf = ast->cntl_op->right->leaf;
	if (cur_leaf)
	{
		preconfig_leaf(shell, cur_leaf);
		if (!ast->cntl_op->right->leaf->r_in)
		{
			if (ast->prev_pipefds && ast->prev_pipefds[0] > 2)
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

	execute_ast(shell, ast->cntl_op->right);
	
	close(ast->pipefds[0]);
	ast->pipefds[0] = -2;
	
	return (0);		// temporaire
}
