/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/22 17:05:58 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_redir_p	new_redir(t_shell *shell, t_redir_p src, char *target)
{
	t_redir_p	new;

	new = _calloc(shell, 1, sizeof(t_redir));
	if (!new)
		return (NULL);
	new->type = src->type;
	new->target = ft_strdup(target);
	if (src->limiter)
		new->limiter = ft_strdup(src->limiter);
	new->fd = src->fd;
	new->next = NULL;
	return (new);
}

static void	redirs_case(t_shell_p shell, t_redir_p redirs, t_expanded *exp)
{
	if (redirs->target)
		*exp = expand_command(shell, redirs->target);
	else if (redirs->limiter)
		*exp = expand_command(shell, redirs->limiter);
}

t_redir_p	_redirs_expand(t_shell *shell, t_redir_p redirs)
{
	t_redir_p	head;
	t_redir_p	curr;
	t_redir_p	new;
	t_expanded	exp;
	t_redir_p	last;

	head = NULL;
	curr = NULL;
	while (redirs)
	{
		(ft_bzero(&exp, sizeof(t_expanded)), redirs_case(shell, redirs, &exp));
		if (!exp.value)
			return (free_redirs(head), NULL);
		new = new_redir(shell, redirs, exp.value);
		free(exp.value);
		if (!new)
			return (free_redirs(head), NULL);
		if (!head)
			head = new;
		else
			curr->next = new;
		curr = new;
		redirs = redirs->next;
	}
	return (head);
}
