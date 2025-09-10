/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   duplicate_fds.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 17:58:54 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/10 12:38:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_open_flag(t_redirtype redirtype)
{
	if (redirtype == R_OUT)
		return (O_WRONLY | O_CREAT | O_TRUNC);
	else if (redirtype == R_APPEND)
		return (O_WRONLY | O_CREAT | O_APPEND);
	else
		return (-1);
}

// open et dup2 a proteger

void	duplicate_fds(t_leaf_p leaf)
{
	int	open_flag;
	
	if (!leaf->r_in && leaf->pipefd[0] >= 0)
	{
		dup2(leaf->pipefd[0], STDIN_FILENO);
	}
	if (!leaf->r_out && leaf->pipefd[1] >= 0)
	{
		dup2(leaf->pipefd[1], STDOUT_FILENO);
	}
	if (leaf->r_in)	
	{
		leaf->fds[0] = open(leaf->r_in_path, O_RDONLY, 0644);
		dup2(leaf->fds[0], STDIN_FILENO);
	}
	if (leaf->r_out)
	{
		open_flag = get_open_flag(leaf->redir->type);
		leaf->fds[1] = open(leaf->r_out_path, open_flag, 0644);
		dup2(leaf->fds[1], STDOUT_FILENO);
	}			
}


// void	duplicate_fds(t_leaf_p leaf)
// {
// 	if (!leaf->r_in && leaf->pipefd[0] >= 0)
// 	{
// /* 		printf("%s -> 1\n", leaf->command_name);
// 		printf("dup1 -> %d\n", dup2(leaf->pipefd[0], STDIN_FILENO)); */
// 		dup2(leaf->pipefd[0], STDIN_FILENO);
// 	}
// 	if (!leaf->r_out && leaf->pipefd[1] >= 0)
// 	{
// /* 		printf("%s -> 2\n", leaf->command_name);
// 		printf("dup2 -> %d\n", dup2(leaf->pipefd[1], STDOUT_FILENO)); */
// 		dup2(leaf->pipefd[1], STDOUT_FILENO);
// 	}
// 	if (leaf->r_in)	
// 	{
// 		leaf->fds[0] = open(leaf->r_in_path, O_RDONLY, 0644);
// /* 		printf("%s -> 3\n", leaf->command_name);
// 		printf("dup3 -> %d\n", dup2(leaf->fds[0], STDIN_FILENO)); */
// 		dup2(leaf->fds[0], STDIN_FILENO);
// 	}
// 	if (leaf->r_out)
// 	{
// 		leaf->fds[1] = open("./out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
// /* 		printf("%s -> 4\n", leaf->command_name);
// 		printf("dup4 -> %d\n", dup2(leaf->fds[1], STDOUT_FILENO));		 */
// 		dup2(leaf->fds[1], STDOUT_FILENO);
// 	}			
// }
