/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_closed_hd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 17:58:01 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/21 13:53:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	set_closed_hd_both_ways(t_ast_p ast)
{
	if (ast->cntl_op->right && ast->cntl_op->right->leaf)
		ast->cntl_op->left->closed_fds = \
			&ast->cntl_op->right->leaf->hd_fd[0];
	else if (ast->cntl_op->right && \
		ast->cntl_op->right->cntl_op->left->leaf)
		ast->cntl_op->left->closed_fds = \
			&ast->cntl_op->right->cntl_op->left->leaf->hd_fd[0];	
}

void	set_closed_hd(t_ast_p ast)
{
	if (ast->cntl_op->right && ast->cntl_op->right->leaf)
		ast->cntl_op->left->closed_fds = \
			&ast->cntl_op->right->leaf->hd_fd[0];
} */

// void	close_hd_fds(t_ast_p origin, t_ast_p cur_node)
// {
// 	if (cur_node->leaf)
// 		origin->closed_fds[origin->i++] = cur_node->leaf->hd_fd[0];
// 	else
// 	{
// 		if (cur_node->cntl_op->left && cur_node->cntl_op->left != origin)
// 			close_hd_fds(origin, cur_node->cntl_op->left);
// 		if (cur_node->cntl_op->right)
// 			close_hd_fds(origin, cur_node->cntl_op->right);
// 	}
// }
