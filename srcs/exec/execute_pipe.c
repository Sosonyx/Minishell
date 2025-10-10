/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipe.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/10 23:35:55 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_pipe(t_shell_p shell, t_ast_p ast)
{
	return (_pipe(shell, ast->cur_pipe));
}

static t_leaf_p	select_right_leaf(t_shell_p shell, t_ast_p ast)
{
	if (ast->cntl_op->right->type == OP_PIPE)
		return (ast->cntl_op->right->cntl_op->right->leaf);
	else
		return (ast->cntl_op->right->leaf);
}

static void	connect_nodes(t_ast_p ast)
{
	close_secure(ast->cntl_op->left->write_fd);
	close_secure(ast->cntl_op->left->closed_fd);
	close_secure(ast->cntl_op->left->read_fd);

	ast->cntl_op->left->write_fd = &ast->cur_pipe[1];
	ast->cntl_op->left->closed_fd = &ast->cur_pipe[0];
	ast->cntl_op->left->read_fd = ast->read_fd;




	close_secure(ast->cntl_op->right->read_fd);
	close_secure(ast->cntl_op->right->closed_fd);
	close_secure(ast->cntl_op->right->write_fd);

	ast->cntl_op->right->read_fd = &ast->cur_pipe[0];
	ast->cntl_op->right->closed_fd = &ast->cur_pipe[1];
	ast->cntl_op->right->write_fd = ast->write_fd;
}

void	execute_pipe(t_shell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		if (open_pipe(shell, ast) == 0)
		{
			static int call_count = 0;
			call_count++;
			printf("call = %d, read_fd: %d, write_fd: %d, closed_fd, cur_pipe[0]: %d,  cur_pipe[1]: %d\n", call_count, ast->read_fd ? *ast->read_fd : -1, ast->write_fd ? *ast->write_fd : -1, ast->closed_fd ? *ast->closed_fd : -1, ast->cur_pipe[0], ast->cur_pipe[0], ast->cur_pipe[1]);
			connect_nodes(ast);
			printf("call = %d, after connect = read_fd: %d, write_fd: %d, closed_fd, cur_pipe[0]: %d,  cur_pipe[1]: %d\n", call_count, ast->read_fd ? *ast->read_fd : -1, ast->write_fd ? *ast->write_fd : -1, ast->closed_fd ? *ast->closed_fd : -1, ast->cur_pipe[0], ast->cur_pipe[0], ast->cur_pipe[1]);

			if (is_no_abort(shell))
			{
				_execute_ast(shell, ast->cntl_op->left);
			}
			close_secure(&ast->cur_pipe[1]);
			close_secure(ast->cntl_op->left->read_fd);

			if (is_no_abort(shell))
			{
				_execute_ast(shell, ast->cntl_op->right);
			}
			close_secure(&ast->cur_pipe[0]);
			wait_if_leaf(ast->cntl_op->left->leaf, NULL);
			wait_if_leaf(select_right_leaf(shell, ast), &shell->exit_code);
		}
		else
			shell->exit_code = ERRVAL1;
	}
}
