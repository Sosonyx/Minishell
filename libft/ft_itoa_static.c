/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_static.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:54:05 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 14:12:32 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	_intlen(int nb)
{
	int		size;

	size = 0;
	if (nb <= 0)
		size += 1;
	while (nb != 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa_static(char *buf, int n)
{
	long	nb;
	int		size;

	if (buf)
	{
		nb = n;
		size = _intlen(n);
		if (nb == 0)
			*buf = '0';
		else if (nb < 0)
		{
			nb = -nb;
			*buf = '-';
		}
		while (nb)
		{
			buf[--size] = (nb % 10 + '0');
			nb /= 10;
		}
	}
	return (buf);
}
