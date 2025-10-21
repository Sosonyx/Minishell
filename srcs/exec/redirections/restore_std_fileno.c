/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_std_fileno.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:42:06 by fox               #+#    #+#             */
/*   Updated: 2025/10/21 14:12:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_fileno(t_shell_p shell, t_ast_p ast)
{
	// printf("cmd %s: restoring stdin -> %d\n", *ast->leaf->cmds, shell->std_fds[0]);
	_dup2(shell, shell->std_fds[0], STDIN_FILENO);
	// printf("cmd %s: restoring stdout -> %d\n", *ast->leaf->cmds, shell->std_fds[1]);
	_dup2(shell, shell->std_fds[1], STDOUT_FILENO);
	close_secure(&shell->std_fds[0]);
	close_secure(&shell->std_fds[1]);
}
