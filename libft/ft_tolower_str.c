/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 12:41:00 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/25 12:44:36 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_tolower_str(char *str)
{
	char	*ptr;

	if (!str)
		return (NULL);
	ptr = str;
	while (*ptr)
	{
		if (ft_isupper(*ptr))
			*ptr = ft_tolower(*ptr);
		ptr++;
	}
	return (str);
}
