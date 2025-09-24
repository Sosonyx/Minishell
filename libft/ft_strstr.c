/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 14:52:31 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/24 18:17:29 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int	lneedle;
	
	if (!(*needle))
		return ((char *) haystack);
	lneedle = ft_strlen(needle);
	while (*haystack)
	{
		if (ft_strncmp(haystack, needle, lneedle) == 0)
			return ((char *) haystack);
		haystack++;
	}
	return (NULL);
}
