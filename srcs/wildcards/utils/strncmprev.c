/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strncmprev.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 14:09:26 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 14:09:41 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

int strncmprev(const char *s1, const char *s2, int size)
{
	int pos_s1;
	int pos_s2;

	if (size <= 0)
		return (0);
	pos_s1 = strlen(s1) - 1;
	pos_s2 = strlen(s2) - 1;
	while (size > 0 && pos_s1 >= 0 && pos_s2 >= 0)
	{
		if (s1[pos_s1] != s2[pos_s2])
			return (s1[pos_s1] - s2[pos_s2]);
		pos_s1--;
		pos_s2--;
		size--;
	}
	return (0);
}
