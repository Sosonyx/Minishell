/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_std_fileno.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:42:06 by fox               #+#    #+#             */
/*   Updated: 2025/10/02 17:15:17 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_fileno(t_minishell_p shell, t_ast_p ast)
{
	if (dup2(shell->std_fds[0], STDIN_FILENO) == -1)
		exit(EXIT_FAILURE);
	if (dup2(shell->std_fds[1], STDOUT_FILENO) == -1)
		exit(EXIT_FAILURE);
	close_secure(&shell->std_fds[0]);
	close_secure(&shell->std_fds[1]);
	close_fds(ast, PARENT);
}
