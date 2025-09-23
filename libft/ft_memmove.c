/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 18:33:50 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/23 19:40:18 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*src2;
	unsigned char	*dest2;

	src2 = (unsigned char *)src;
	dest2 = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (dest2 < src2)
		while (n--)
			*dest2++ = *src2++;
	else
		while (n--)
			dest2[n] = src2[n];
	return (dest);
}
