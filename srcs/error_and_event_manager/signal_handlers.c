/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 16:30:13 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/15 18:31:03 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	signals_setter(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_setter_exec(void)
{
	signal(SIGINT, sigint_handler_exec);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	signals_dfl(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	heredoc_signal_handler(int sig)
{
	(void)sig;
	printf("%d\n",sig);
	write(1, "\n", 1);
	g_sigstatus = sig;
	close(0);
}
