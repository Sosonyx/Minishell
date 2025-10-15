/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_rstatus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/10 14:39:35 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/10 14:39:39 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	extract_return_code(int status)
{
	int	return_status;

	printf("exit status = %d\n", status);
	if (status == -1)
		return_status = EXIT_FAILURE;
	else if (WIFEXITED(status))
		return_status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		return_status = WTERMSIG(status) << 7;
	else if (WIFSTOPPED(status))
		return_status = WSTOPSIG(status);
	else if (WIFCONTINUED(status))
		return_status = EXIT_FAILURE;
	else
		return_status = EXIT_SUCCESS;
	return (return_status);
}
