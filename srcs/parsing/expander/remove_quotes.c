/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:49:31 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/17 14:10:14 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_state(t_redir_p redirs, int state, char c)
{
	state = quote_state(state, c);
	if (redirs && state)
		redirs->expand_hd = 1;
	return (state);
}

char	*remove_quotes(t_shell_p shell, t_redir_p redirs, char *str)
{
	char	*res;
	int		i;
	int		j;
	int		state;

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
	free(str);
	return (res);
}
