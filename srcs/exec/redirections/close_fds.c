/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   close_fds.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/08 16:49:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/10 11:38:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds(t_leaf_p leaf)
{
	if (leaf->fds[0] > 2)
		close(leaf->fds[0]);
	if (leaf->fds[1] > 2)
		close(leaf->fds[1]);
/* 	if (leaf->pipefd[0] > 2)
		close(leaf->pipefd[0]);
	if (leaf->pipefd[1] > 2)
		close(leaf->pipefd[1]);		 */
}
