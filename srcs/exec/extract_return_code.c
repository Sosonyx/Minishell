/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_return_code.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 12:09:17 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 12:18:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_return_code(int *status)
{
	int return_status;
	
	if (WIFEXITED(*status))
	{
		return_status = WEXITSTATUS(*status);
	}
	else if (WIFSIGNALED(*status))
	{
		return_status = WCOREDUMP(*status);
		if (!return_status)
			return_status = WTERMSIG(*status);
	}
	else if (WIFSTOPPED(*status))
	{
		return_status = WSTOPSIG(*status);
	}
	else if (WIFCONTINUED(*status))
	{
		return_status = EXIT_FAILURE;
	}
	else
	{ 
		return_status = EXIT_SUCCESS;
	}
	return (return_status);	
}
