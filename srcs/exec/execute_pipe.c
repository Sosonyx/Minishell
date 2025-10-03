/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/03 17:37:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_pipe(t_minishell_p shell, t_ast_p ast)
{
	ast->cur_pipe = ft_calloc(2, sizeof(int));
	if (ast->cur_pipe)
	{
		return (_pipe(shell, ast->cur_pipe));
	}
	else
		return (set_abort(shell, MEM_ERRMSG), RETURN_FAIL);
}

static void	connect_nodes(t_ast_p ast)
{
	ast->cntl_op->left->write_fd = &ast->cur_pipe[1];
	ast->cntl_op->left->read_fd = ast->read_fd;
	ast->cntl_op->left->closed_fd = &ast->cur_pipe[0];
	ast->cntl_op->right->read_fd = &ast->cur_pipe[0];
	ast->cntl_op->right->write_fd = ast->write_fd;
	ast->cntl_op->right->closed_fd = &ast->cur_pipe[1];
}

void	execute_pipe(t_minishell_p shell, t_ast_p ast)
{
	if (open_pipe(shell, ast) == 0)
	{
		connect_nodes(ast);
		_execute_ast(shell, ast->cntl_op->left);
		close_secure(&ast->cur_pipe[1]);
		if (is_no_abort(shell))
		{
			_execute_ast(shell, ast->cntl_op->right);
			close_secure(&ast->cur_pipe[0]);
		}
		wait_if_leaf(ast->cntl_op->left->leaf, NULL);
		if (ast->cntl_op->right->type == OP_PIPE)
			wait_if_leaf(ast->cntl_op->right->cntl_op->right->leaf, &shell->exit_code);
		else
			wait_if_leaf(ast->cntl_op->right->leaf, &shell->exit_code);
		free(ast->cur_pipe);
	}
	else
		shell->exit_code = ERRVAL1;
}
