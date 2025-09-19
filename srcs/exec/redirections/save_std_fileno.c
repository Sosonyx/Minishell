/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_std_fileno.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/19 10:42:04 by fox               #+#    #+#             */
/*   Updated: 2025/09/19 10:42:05 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void save_std_fileno(t_minishell_p shell)
{
    shell->std_fds[0] = dup(STDIN_FILENO);
    shell->std_fds[1] = dup(STDOUT_FILENO);
}   
