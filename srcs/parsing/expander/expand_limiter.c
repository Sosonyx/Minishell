/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:21:38 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/03 16:36:28 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_state(t_redir_p redirs, int state, char c)
{
	if (c == '\'' && state == 0)
		return (redirs->expand_hd = 1, 1);
	else if (c == '\'' && state == 1)
		return (0);
	else if (c == '"' && state == 0)
		return (redirs->expand_hd = 1, 2);
	else if (c == '"' && state == 2)
		return (0);
	return (state);
}

static char	*remove_quotes(t_redir_p redirs, char *str)
{
	char	*res;
	int		i;
	int		j;
	int		state;
	int		new_state;

	if (!str)
		return (NULL);
	res = malloc(ft_strlen(str) + 1);
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

char	*expand_limiter(t_redir_p redirs, char *str)
{
	char	*new_limiter;

	new_limiter = remove_quotes(redirs, str);
	if (!new_limiter)
		return (NULL);
	return (new_limiter);
}
