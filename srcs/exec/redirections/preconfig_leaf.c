/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preconfig_leaf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:43:19 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/01 15:28:04 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_command_path(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;

	ast->leaf->full_path = find_cmd(shell, ast);
}

static void	redir_in_conf(t_leaf_p leaf)
{
	t_redir_p	cur_redir;
	char		*target;

	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_IN || cur_redir->type == R_HDOC)
		{
			target = cur_redir->target;
			leaf->r_in = true;
			leaf->r_in_path = target;
		}
		cur_redir = cur_redir->next;
	}
}

static void	redir_out_conf(t_leaf_p leaf)
{
	char		*target;
	t_redir_p	cur_redir;

	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_OUT || cur_redir->type == R_APPEND)
		{
			target = cur_redir->target;
			leaf->r_out = true;
			leaf->r_out_path = target;
		}
		cur_redir = cur_redir->next;
	}
}

void	preconfig_leaf(t_minishell_p shell, t_ast_p ast)
{
	redir_in_conf(ast->leaf);
	redir_out_conf(ast->leaf);
	get_command_path(shell, ast);
	ast->leaf->configured = true;
}
