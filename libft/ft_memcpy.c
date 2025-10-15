/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/23 17:48:42 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/15 22:44:45 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	t_byte	*to;
	t_byte	*from;

	if (src && dest)
	{
		to = (t_byte *) dest;
		from = (t_byte *) src;
		while (n-- != 0)
			*to++ = *from++;
	}
	return (dest);
}
