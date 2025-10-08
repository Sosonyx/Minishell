/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/06 14:22:06 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/08 12:32:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*_malloc(t_shell_p shell, size_t size)
{
	void	*ptr;
	
	ptr = NULL;
	if (is_no_abort(shell))
	{
		ptr = malloc(size);
		if (!ptr)
			set_abort(shell, MEM_ERRMSG);
		return (ptr);
	}
	else
		return (NULL);
}

void	*_calloc(t_shell_p shell, size_t nmemb, size_t size)
{
	void	*ptr;

	if (is_no_abort(shell))
	{
		ptr = ft_calloc(nmemb, size);
		if (!ptr)
		set_abort(shell, MEM_ERRMSG);
		return (ptr);
	}
	else
		return (NULL);
}

void	*_realloc(t_shell_p shell, void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;

	if (is_no_abort(shell))
	{
		new_ptr = ft_calloc(new_size, sizeof(t_byte));
		if (new_ptr)
		{
			ft_memcpy(new_ptr, ptr, old_size);
			free(ptr);
		}
		else
		{
			set_abort(shell, MEM_ERRMSG);
		}
		return (new_ptr);
	}
	else
		return (NULL);
}
