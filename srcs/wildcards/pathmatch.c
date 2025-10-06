/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/10/06 11:37:38 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	_compare(char c1, char c2)
{
	return (c1 - c2);
}

static int	_pathmatch(char *ptested, char *pref, bool any)
{
	if (*pref && isasterisk(*pref))
	{
		return (_pathmatch(ptested, pref + 1, true));
	}
	else if (*pref)
	{
		if (any)
		{
			if (*(pref + 1))
			{
				while (*ptested && _compare(*ptested, *pref))
					++ptested;
				if (*ptested)
					return (_pathmatch(ptested + 1, pref + 1, false));
				else
					return (0);
			}
			else
			{
				while (*(ptested + 1))
					++ptested;
				return (!_compare(*ptested, *pref));
			}
		}
		else
		{
			if (_compare(*ptested, *pref))
				return (0);
			else
				return (_pathmatch(ptested + 1, pref + 1, false));
		}
	}
	else
	{
		if (*ptested)
			return (any);
		else
			return (1);
	}
}

int	pathmatch(char *ptested, char *pref)
{
	return (_pathmatch(ptested, pref, isasterisk(*pref)));
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
