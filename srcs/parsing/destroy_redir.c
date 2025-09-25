/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_redir.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/25 10:25:20 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/25 10:25:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	destroy_redir_node(t_redir_p node)
{
	if (node)
	{
		free(node->limiter);
		free(node->target);
		free(node);
	}
}

void	destroy_redir(t_ast_p ast)
{
	t_redir_p	cur_redir;
	t_redir_p	next_redir;;
	
	cur_redir = ast->leaf->redir;
	while (cur_redir)
	{
		next_redir = cur_redir->next;
		destroy_redir_node(cur_redir);
		cur_redir = next_redir;
	}
}
