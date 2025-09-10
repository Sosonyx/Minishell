/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:43:19 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/10 14:11:08 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_redir_in(t_leaf_p leaf)
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

static void	get_redir_out(t_leaf_p leaf)
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

void	get_redirections(t_leaf_p leaf)
{
	get_redir_in(leaf);
	get_redir_out(leaf);
	leaf->treated = true;
}
