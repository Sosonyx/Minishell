/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_kill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:54:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/12 13:38:56 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_kill(t_shell_p shell)
{
	print_generic_error(shell, "Fatal error. Exit now...\n");
	if (shell)
		destroy_shell(shell);
	exit(EXIT_FAILURE);
}
