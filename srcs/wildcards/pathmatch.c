/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/10/07 18:16:12 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	_compare(char c1, char c2)
{
	return (c1 - c2);
}

static int	has_a_star(int state, char *str)
{
	str++;
	while (*str)
	{
		if ((state == 1 && *str == '\'') || (state == 2 && *str == '"'))
			break ;
		if (*str == '\'')
			state = 1;
		else if (*str == '"')
			state = 2;
		if (*str == '*')
		{
			while (*str)
			{
				if ((state == 1 && *str == '\'') || (state == 2 && *str == '"'))
					return (1);
				else
					return (0);
				str++;
			}
		}
		str++;
	}
	return (0);
}

int	pathmatch(char *ptested, char *pref, int state)
{
	if (!*ptested && !*pref)
		return (1);

	if ((*pref == '\'' && state != 2) || (*pref == '"' && state != 1))
		state = quote_state(state, *pref++);

	if (!isasterisk(*pref) || state)
	{
		if (_compare(*ptested, *pref))
			return (0);
		else
			return (pathmatch(ptested + 1, pref + 1, state));
	}
	while (isasterisk(*pref) && !state)
	{
		pref++;
		if (!*pref)
			return (1);
	}

	while (*ptested)
		if (pathmatch(ptested++, pref, state))
			return (1);
			
	return (0);
}

// int	main(int argc, char **argv)
// {
// 	int		result = _pathmatch(argv[1], argv[2], argv[2][1] == '*');
// 	printf("result> %d\n", result);
// 	return (0);
// }

// int	main(void)
// {
// 	char	*comp = "build";
// 	char	*pref = "*ss";
// 	int		result = _pathmatch(comp, pref, *pref == '*');
// 	printf("result> %d\n", result);
// 	return (0);
// }
