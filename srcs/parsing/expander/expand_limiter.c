/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:21:38 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/06 18:51:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_state(t_redir_p redirs, int state, char c)
{
	if (c == '\'' && state == 0)
	{
		if (redirs)
			redirs->expand_hd = 1;
		return (1);
	}
	else if (c == '\'' && state == 1)
		return (0);
	else if (c == '"' && state == 0)
	{
		if (redirs)
			redirs->expand_hd = 1;
		return (2);
	}
	else if (c == '"' && state == 2)
		return (0);
	return (state);
}

char	*remove_quotes(t_minishell_p shell, t_redir_p redirs, char *str)
{
	char	*res;
	int		i;
	int		j;
	int		state;
	int		new_state;

	if (!str)
		return (NULL);
	res = _malloc(shell, ft_strlen(str) + 1);
	if (!res)
		return (NULL);
	i = 0;
	j = 0;
	state = 0;
	while (str[i])
	{
		if ((str[i] == '\'' && state != 2) || (str[i] == '"' && state != 1))
			state = update_state(redirs, state, str[i]);
		else
			res[j++] = str[i];
		i++;
	}
	res[j] = '\0';
	return (res);
}

char	*expand_limiter(t_minishell_p shell, t_redir_p redirs, char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
	{
		redirs->expand_hd = 1;
		return (remove_quotes(shell, redirs, str));
	}
	else
		return (_strdup(shell, str));
}
