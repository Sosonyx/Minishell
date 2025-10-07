/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 13:54:40 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 14:35:45 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	quote_state(int state, char c)
{
	if (c == '\'' && state == 0)
		state = 1;
	else if (c == '\'' && state == 1)
		state = 0;
	else if (c == '"' && state == 0)
		state = 2;
	else if (c == '"' && state == 2)
		state = 0;
	return (state);
}
