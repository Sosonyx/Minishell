/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_std_fileno.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:42:06 by fox               #+#    #+#             */
/*   Updated: 2025/10/20 20:14:56 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_fileno(t_shell_p shell, t_ast_p ast)
{
	_dup2(shell, shell->std_fds[0], STDIN_FILENO);
	_dup2(shell, shell->std_fds[1], STDOUT_FILENO);
	close_secure(&shell->std_fds[0]);
	close_secure(&shell->std_fds[1]);
	close_fds(shell, ast, PARENT);
}
