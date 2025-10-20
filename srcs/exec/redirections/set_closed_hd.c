/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_closed_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:58:01 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/20 18:44:18 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_closed_hd_both_ways(t_ast_p ast)
{
	if (ast->cntl_op->right && ast->cntl_op->right->leaf)
		ast->cntl_op->left->closed_hd_fd = \
			&ast->cntl_op->right->leaf->hd_fd[0];
	else if (ast->cntl_op->right && \
		ast->cntl_op->right->cntl_op->left->leaf)
		ast->cntl_op->left->closed_hd_fd = \
			&ast->cntl_op->right->cntl_op->left->leaf->hd_fd[0];	
}

void	set_closed_hd(t_ast_p ast)
{
	if (ast->cntl_op->right && ast->cntl_op->right->leaf)
		ast->cntl_op->left->closed_hd_fd = \
			&ast->cntl_op->right->leaf->hd_fd[0];
}

// void	close_hd_fds(t_ast_p ast)
// {
// 	if (ast->leaf)
// 		return (close_secure(&ast->closed_hd_fd));
// 	else
// 	{
// 		if (ast->cntl_op->left)
// 			close_hd_fds(ast->cntl_op->left);
// 		if (ast->cntl_op->right)
// 			close_hd_fds(ast->cntl_op->right);
// 	}
// }
