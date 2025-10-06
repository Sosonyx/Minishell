/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pathmatch.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:34:09 by fox               #+#    #+#             */
/*   Updated: 2025/10/06 20:47:16 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	_compare(char c1, char c2)
{
	return (c1 - c2);
}

int	pathmatch(char *ptested, char *pref)
{
	if (!*ptested && !*pref)
		return (1);
	if (!isasterisk(*pref))
	{
		if (_compare(*ptested, *pref))
			return (0);
		else
			return (pathmatch(ptested + 1, pref + 1));
	}
	while (isasterisk(*pref))
	{
		pref++;
		if (!*pref)
			return (1);
	}
	while (*ptested)
		if (pathmatch(ptested++, pref))
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
