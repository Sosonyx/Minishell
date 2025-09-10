/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/10 11:57:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	duplicate_fds(t_leaf_p leaf)
{
	if (!leaf->r_in && leaf->pipefd[0] >= 0)
	{
		printf("%s -> 1\n", leaf->command_name);
		printf("dup1 -> %d\n", dup2(leaf->pipefd[0], STDIN_FILENO));
	}
	if (!leaf->r_out && leaf->pipefd[1] >= 0)
	{
		printf("%s -> 2\n", leaf->command_name);
		printf("dup2 -> %d\n", dup2(leaf->pipefd[1], STDOUT_FILENO));
	}
	if (leaf->r_in && leaf->fds[0] != STDIN_FILENO)	
	// if (leaf->r_in)	
	{
		printf("%s -> 3\n", leaf->command_name);
		printf("dup3 -> %d\n", dup2(leaf->fds[0], STDIN_FILENO));
	}
	if (leaf->r_out && leaf->fds[1] != STDOUT_FILENO)
	// if (leaf->r_out)	
	{
		printf("%s -> 4\n", leaf->command_name);
		// leaf->fds[1] = open("./out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
		printf("dup4 -> %d\n", dup2(leaf->fds[1], STDOUT_FILENO));
	}			
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
