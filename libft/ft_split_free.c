/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_free.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 19:11:25 by cgajean           #+#    #+#             */
/*   Updated: 2025/06/26 16:36:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_split_free(char **strs)
{
	char	**ptr_to_strs;

	if (!strs)
		return ;
	ptr_to_strs = strs;
	while (*ptr_to_strs)
		free(*ptr_to_strs++);
	free(strs);
}
