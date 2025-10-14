/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:04:20 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 14:04:19 by ihadj            ###   ########.fr       */
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
	destroy_redir(ast);
	free(ast->leaf);
}
