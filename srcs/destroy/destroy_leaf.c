/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:04:20 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/15 22:55:05 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_leaf(t_ast_p ast)
{
	ft_split_free(ast->leaf->cmds);
	if (ast->leaf->exec_path)
		free(ast->leaf->exec_path);
	if (ast->leaf->full_path)
		free(ast->leaf->full_path);
	if (ast->leaf->is_heredoc)
		close_secure(&ast->leaf->hd_fd[0]);
	destroy_redir(ast);
	free(ast->leaf);
}
