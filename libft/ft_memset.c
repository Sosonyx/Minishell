/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 10:29:04 by cgajean           #+#    #+#             */
/*   Updated: 2025/07/18 15:42:12 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_op_t	define_pattern(int c)
{
	size_t	opsiz;
	t_op_t	pattern;

	opsiz = sizeof(t_op_t);
	pattern = (unsigned char) c;
	pattern |= pattern << 8;
	pattern |= pattern << 16;
	if (opsiz > 4)
		pattern |= (pattern << 16) << 16;
	return (pattern);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*dst;
	t_op_t			*dst_op;
	t_op_t			pattern;
	size_t			opsiz;

	if (!s)
		return (NULL);
	dst = (unsigned char *) s;
	pattern = define_pattern(c);
	opsiz = sizeof(t_op_t);
	while (n > 0 && ((uintptr_t) dst % opsiz != 0))
	{
		*dst++ = (unsigned char)c;
		--n;
	}
	dst_op = (t_op_t *) dst;
	while (n >= opsiz)
	{
		*dst_op++ = pattern;
		n -= opsiz;
	}
	dst = (unsigned char *) dst_op;
	while (n--)
		*dst++ = (unsigned char)c;
	return (s);
}
