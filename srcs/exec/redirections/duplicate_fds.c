/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 19:45:31 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_fds(t_leaf_p leaf)
{
	if (leaf->pipefd[0] > 2)
	{
		dup2(leaf->pipefd[0], leaf->fds[0]);
		close(leaf->pipefd[0]);
	}
	if (leaf->pipefd[1] > 2)
	{
		dup2(leaf->pipefd[1], leaf->fds[1]);
		close(leaf->pipefd[1]);
	}
	dup2(leaf->fds[0], STDIN_FILENO);
	dup2(leaf->fds[1], STDOUT_FILENO);
}

/* void	duplicate_fds(t_leaf_p leaf)
{
	if (!leaf->r_in && leaf->pipefd[0] > 2)
	{
		dup2(leaf->pipefd[0], leaf->fds[0]);
		close(leaf->pipefd[0]);
	}
	if (!leaf->r_out && leaf->pipefd[1] > 2)
	{
		dup2(leaf->pipefd[1], leaf->fds[1]);
		close(leaf->pipefd[1]);
	}
	dup2(leaf->fds[0], STDIN_FILENO);
	dup2(leaf->fds[1], STDOUT_FILENO);
} */
