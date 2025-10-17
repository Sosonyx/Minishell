/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/17 19:33:46 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redirs(t_redir_p list)
{
	t_redir_p	tmp;

	while (list)
	{
		tmp = list->next;
		free(list->target);
		free(list->limiter);
		free(list);
		list = tmp;
	}
}

static char	**split_redir_target(t_expanded exp)
{
	if (exp.split_allowed)
		return (ft_split(exp.value, ' '));
	return (ft_split(exp.value, '\0'));
}

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

static t_redir_p	append_redirs(t_shell *shell, t_redir_p src, \
	char **splitted, t_redir_p curr)
{
	int			i;
	t_redir_p	new;

	i = -1;
	while (splitted[++i])
	{
		new = new_redir(shell, src, splitted[i]);
		if (!new)
			return (NULL);
		if (!curr)
			curr = new;
		else
			curr->next = new;
		curr = new;
	}
	return (curr);
}

t_redir_p	_redirs_expand(t_shell *shell, t_redir_p redirs)
{
	t_redir_p	head;
	t_redir_p	curr;
	char		**splitted;
	t_expanded	exp;
	t_redir_p	last;

	head = NULL;
	curr = NULL;
	while (redirs)
	{
		if (redirs->target)
			exp = expand_command(shell, redirs->target);
		else if (redirs->limiter)
			exp = expand_command(shell, redirs->limiter);
		if (!exp.value)
			return (free_redirs(head), NULL);
		splitted = split_redir_target(exp);
		free(exp.value);
		if (!splitted)
			return (free_redirs(head), NULL);
		last = append_redirs(shell, redirs, splitted, curr);
		if (!last)
			return (ft_split_free(splitted), free_redirs(head), NULL);
		(head == 0 && (head = last));
		curr = last;
		(ft_split_free(splitted), redirs = redirs->next);
	}
	return (head);
}
