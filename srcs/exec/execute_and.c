/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_and.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:34 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/09 20:30:25 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_and(t_shell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		forward_fds(ast);
		_execute_ast(shell, ast->cntl_op->left);
		wait_if_leaf(ast->cntl_op->left->leaf, &shell->exit_code);
	}
	if (is_no_abort(shell) && !shell->exit_code && ast->cntl_op->right)
	{
		_execute_ast(shell, ast->cntl_op->right);
		close_secure(ast->read_fd);
			// close_fds(ast, CHILD);

		wait_if_leaf(ast->cntl_op->right->leaf, &shell->exit_code);
	}
}
