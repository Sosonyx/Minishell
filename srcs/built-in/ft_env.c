/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/07 16:18:00 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/24 17:30:31 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_minishell_p shell, char **args)
{
	int	i;

	if (args && args[1])
	{
		print_cmd_error2(shell, "env", ARG_EXCESS_ERRMSG);
		return (ERRVAL1);
	}
	i = -1;
	while (shell->environ[++i])
		ft_printf("%s\n", shell->environ[i]);
	return (EXIT_SUCCESS);
}
