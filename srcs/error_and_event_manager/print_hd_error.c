/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hd_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 17:20:38 by fox               #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	get_msglen(t_shell_p shell, char *limiter)
{
	size_t	msglen;

	msglen = ft_strlen("here-document at line ");
	msglen += LEN_INTMAX;
	msglen += ft_strlen(" delimited by end-of-file (wanted `");
	msglen += ft_strlen(limiter);
	msglen += ft_strlen("')");
	return (msglen);
}

static char *get_errmsg(t_shell_p shell, char *limiter, size_t msglen)
{
	char	*errmsg;
	char	*line_nb;
	
	line_nb = ft_itoa(shell->readlines);
	if (!line_nb)
	{
		print_generic_error(shell, MEM_ERRMSG);
		;	// exit
	}
	errmsg = ft_calloc(msglen + 1, sizeof(char));
	if (errmsg)
	{
		errmsg = ft_strcat(errmsg, "here-document at line ");
		errmsg = ft_strcat(errmsg, line_nb);
		errmsg = ft_strcat(errmsg, " delimited by end-of-file (wanted `");
		errmsg = ft_strcat(errmsg, limiter);
		errmsg = ft_strcat(errmsg, "')");
	}
	free(line_nb);
	return (errmsg);
}

void	print_hd_error(t_shell_p shell, char *limiter)
{
	char	*errmsg;
	size_t	msglen;

	msglen = get_msglen(shell, limiter);
	errmsg = get_errmsg(shell, limiter, msglen);
	if (errmsg)
	{			
		speak(shell, STDERR_FILENO, "warning", COLUMN);
		speak(NULL, STDERR_FILENO, errmsg, NEWLINE);
		free(errmsg);
	}
	else
	{
		print_generic_error(shell, MEM_ERRMSG);
		;	//	sortir
	}
}
