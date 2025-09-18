/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:21:55 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipe(t_minishell_p shell, t_ast_p ast)
{
	int	pipe_return;

	ast->cur_pipe = ft_calloc(2, sizeof(int));
	if (ast->cur_pipe)
	{
		pipe_return = pipe(ast->cur_pipe);
		if (pipe_return == -1)
			return (print_generic_error(shell, PIP_ERRMSG), -1);
	}
	else
	{
		return (print_generic_error(shell, MEM_ERRMSG), -1);
	}
	return (0);
}

static void	connect_nodes(t_ast_p ast)
{
	ast->cntl_op->left->write_fd = &ast->cur_pipe[1];
	ast->cntl_op->left->read_fd = ast->read_fd;
	
	ast->cntl_op->right->read_fd = &ast->cur_pipe[0];
	ast->cntl_op->right->write_fd = ast->write_fd;
}

int execute_pipe(t_minishell_p shell, t_ast_p ast)
{	
	if (create_pipe(shell, ast) == -1) 
		return (-1);

	connect_nodes(ast);

	shell->last_status = _execute_ast(shell, ast->cntl_op->left);
	close_secure(&ast->cur_pipe[1]);

	shell->last_status = _execute_ast(shell, ast->cntl_op->right);
	close_secure(&ast->cur_pipe[0]);

	wait_if_leaf(ast->cntl_op->left->leaf, &shell->last_status);
	wait_if_leaf(ast->cntl_op->right->leaf, &shell->last_status);
		
	return (shell->last_status);
}
