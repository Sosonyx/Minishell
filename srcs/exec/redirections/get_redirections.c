/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 15:43:19 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/10 12:20:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	close_prev(int prev)
{
	if (prev > 2)
		close(prev);
}

static int	get_open_flag(t_redirtype redirtype)
{
	if (redirtype == R_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirtype == R_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

static void	get_redir_in(t_leaf_p leaf)
{
	char 		*target;
	int 		prev;
	t_redir_p	cur_redir;

	prev = 0;
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
	int			prev = 0;
	t_redir_p	cur_redir;
	int			open_flags;
	
	cur_redir = leaf->redir;
	while (cur_redir)
	{
		open_flags = get_open_flag(cur_redir->type);
		if (open_flags != -1)
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
}
