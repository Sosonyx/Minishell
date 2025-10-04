/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_std_fileno.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:42:04 by fox               #+#    #+#             */
/*   Updated: 2025/10/03 15:44:47 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	save_std_fileno(t_minishell_p shell)
{
	shell->std_fds[0] = _dup(shell, STDIN_FILENO);
	shell->std_fds[1] = _dup(shell, STDOUT_FILENO);
}
