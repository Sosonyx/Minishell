/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_command.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 15:45:36 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 14:05:03 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_state(int state, char c, t_expanded *exp)
{
	state = quote_state(state, c);
	if (exp && state)
			exp->split_allowed = 0;
	return (state);
}

t_expanded	expand_command(t_shell *shell, char *str)
{
	int			i;
	int			state;
	int			new_state;
	t_expanded	result;

	result.value = ft_strdup("");
	result.split_allowed = 1;
	if (!result.value)
		return (result);
	state = 0;
	i = 0;
	while (str && str[i])
	{
		new_state = update_state(state, str[i], &result);
		if (new_state != state)
		{
			state = new_state;
			result.value = append_char(result.value, str[i]);
		}
		else if (str[i] == '$' && state != 1)
			exp_case(shell, str, &result, &i);
		else
			result.value = append_char(result.value, str[i]);
		if (!result.value)
			return (result);
		i++;
	}
	return (result);
}
