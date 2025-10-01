/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   restore_std_fileno.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:42:06 by fox               #+#    #+#             */
/*   Updated: 2025/10/01 15:25:37 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	restore_std_fileno(t_minishell_p shell, t_ast_p ast)
{
	dup2(shell->std_fds[0], STDIN_FILENO);
	dup2(shell->std_fds[1], STDOUT_FILENO);
	close_secure(&shell->std_fds[0]);
	close_secure(&shell->std_fds[1]);
	close_fds(ast, PARENT);
}
