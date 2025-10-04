/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_setters.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:02:58 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/04 16:42:54 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_signal_error(t_minishell_p shell)
{
	if (shell->exit_code == SIGINT)
		printf("\n");
	else if (shell->exit_code == SIGQUIT + 128)
		printf("Quit (core dumped)\n");
}

void	sigint_handler(int sig)
{
	(void) sig;
	g_sigstatus = 0;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	sigint_handler_exec(int sig)
{
	g_sigstatus = sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();

}
