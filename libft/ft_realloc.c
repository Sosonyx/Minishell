/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 17:47:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/03 16:28:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void **ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(new_size, sizeof(t_byte));
	if (new_ptr == NULL)
		return (NULL);
	else
	{
		ft_memcpy(new_ptr, *ptr, old_size);
		free(*ptr);
	}
	return (new_ptr);
}
