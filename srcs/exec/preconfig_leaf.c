/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   configure_leaf.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:43:19 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/11 16:26:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_command_path(t_minishell_p shell, t_leaf_p leaf)
{
	char *cmd;
	
	leaf->command_name = leaf->cmds[0];
	cmd = find_cmd(leaf->cmds[0], shell->environ);
	if (cmd)
		leaf->cmds[0] = cmd;
}

static void	redir_in_conf(t_leaf_p leaf)
{
	char 		*target;
	t_redir_p	cur_redir;

	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_IN)
		{
			target = cur_redir->target;
			if (access(target, R_OK) == -1)
			{
				print_file_error(target, ENOENT);
				//	traiter si fichier pas ok, pour l'instant je suppose les fichiers OK
				break;
			}
			else
			{
				leaf->r_in = true;
				leaf->r_in_path = target;
			}
		}
		cur_redir = cur_redir->next;
	}
}

static void	redir_out_conf(t_leaf_p leaf)
{
	char 		*target;
	t_redir_p	cur_redir;
	
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		if (cur_redir->type == R_OUT || cur_redir->type == R_APPEND)
		{
			target = cur_redir->target;
			if (access(target, F_OK) == 0 && (access(target, W_OK) == -1))
			{
				print_file_error(target, ENOENT);
				//	traiter si fichier pas ok, pour l'instant je suppose les fichiers OK
				break;
			}
			else
			{
				leaf->r_out = true;
				leaf->r_out_path = target;
			}
		}
		cur_redir = cur_redir->next;
	}
}

void	preconfig_leaf(t_minishell_p shell, t_leaf_p leaf)
{
	redir_in_conf(leaf);
	redir_out_conf(leaf);
	get_command_path(shell, leaf);
	leaf->configured = true;
}
