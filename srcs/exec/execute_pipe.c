/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/12 19:56:55 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	create_pipe(t_ast_p ast)
{
	int	pipe_return;

	ast->cur_pipe = ft_calloc(2, sizeof(int));
	if (ast->cur_pipe)
	{
		pipe_return = pipe(ast->cur_pipe);
		if (pipe_return == -1)
			return (print_generic_error(PIP_ERRMSG), -1);
	}
	else
	{
		return (print_generic_error(MEM_ERRMSG), -1);
	}
	return (0);
}

int execute_pipe(t_minishell_p shell, t_ast_p ast)
{
	t_leaf_p	cur_leaf;
	t_cntl_op_p	cur_cntl;
	int			ret_code;
	
	/************************************************** */
	/* pipe */
		
	if (create_pipe(ast) == -1) return (-1);


	/************************************************** */
	/* redir */

	ast->cntl_op->left->write_fd = &ast->cur_pipe[1];
	ast->cntl_op->left->read_fd = ast->read_fd;
	
	ast->cntl_op->right->read_fd = &ast->cur_pipe[0];
	ast->cntl_op->right->write_fd = ast->write_fd;

	/************************************************** */
	/* left */

	ret_code = execute_ast(shell, ast->cntl_op->left);
	close_secure(&ast->cur_pipe[1]);
	
	
	/************************************************** */
	/* right */
	
	ret_code = execute_ast(shell, ast->cntl_op->right);
	close_secure(&ast->cur_pipe[0]);
	
	return (ret_code);
}
