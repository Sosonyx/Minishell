/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_redirs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 16:44:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 16:57:26 by ihadj            ###   ########.fr       */
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

t_redir_p	_redirs_expand(t_shell *shell, t_redir_p redirs)
{
	t_redir_p	head;
	t_redir_p	curr;
	t_redir_p	new;
	char		**splitted;
	t_expanded	exp;
	int			i;

	head = NULL;
	curr = NULL;
	while (redirs)
	{
		exp = expand_command(shell, redirs->target);
		if (!exp.value)
			return (free_redirs(head), NULL);
		if (exp.split_allowed == true)
			splitted = ft_split(exp.value, ' ');
		else
			splitted = ft_split(exp.value, '\0');
		free(exp.value);
		i = 0;
		while (splitted[i])
		{
			new = ft_calloc(1, sizeof(t_redir));
			if (!new)
			{
				ft_split_free(splitted);
				return (free_redirs(head), NULL);
			}
			new->type = redirs->type;
			new->target = ft_strdup(splitted[i]);
			if (redirs->limiter)
				new->limiter = ft_strdup(redirs->limiter);
			new->fd = redirs->fd;
			new->next = NULL;
			if (!head)
				head = new;
			else
				curr->next = new;
			curr = new;
			i++;
		}
		ft_split_free(splitted);
		redirs = redirs->next;
	}
	return (head);
}
