/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:22:06 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*_malloc(t_shell_p shell, size_t size)
{
	void	*ptr;
	
	ptr = malloc(size);
	if (!ptr)
		set_abort(shell, MEM_ERRMSG);
	return (ptr)	;
}

void	*_calloc(t_shell_p shell, size_t nmemb, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(nmemb, size);
	if (!ptr)
		set_abort(shell, MEM_ERRMSG);
	return (ptr);
}

void	*_realloc(t_shell_p shell, void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	new_ptr = ft_calloc(new_size, sizeof(t_byte));
	if (new_ptr)
	{
		ft_memcpy(new_ptr, ptr, old_size);
		free(ptr);
	}
	else
		set_abort(shell, MEM_ERRMSG);
	return (new_ptr);
}
