/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:04:20 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 18:58:51 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_leaf(t_ast_p ast)
{
	ft_split_free(ast->leaf->cmds);
	if (ast->leaf->exec_path)
		free(ast->leaf->exec_path);
	destroy_redir(ast);
	free(ast->leaf);
	ast->leaf = NULL;
}
