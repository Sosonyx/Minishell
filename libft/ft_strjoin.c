/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 18:21:58 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/23 19:37:06 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	s1size = 0;
	size_t	s2size = 0;
	char	*ptr;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s1)
		s1size = strlen(s1);
	if (s2)
		s2size = strlen(s2);
	ptr = ft_calloc(s1size + s2size + 1, sizeof(char));
	if (!ptr)
		return (NULL);
	while (s1 && s1[i])
	{
		ptr[i] = s1[i];
		i++;
	}
	while (s2 && (i + j) < (s1size + s2size + 1))
	{
		ptr[i + j] = s2[j];
		j++;
	}
	return (ptr);
}
