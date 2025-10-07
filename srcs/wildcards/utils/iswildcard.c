/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iswildcard.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:29:03 by fox               #+#    #+#             */
/*   Updated: 2025/10/07 16:17:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

int	iswildcard(char *field)
{
	if (field)
	{
		while (*field)
		{
			if (isasterisk(*field++))
				return (1);
		}
	}
	return (0);
}
