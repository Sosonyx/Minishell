/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:04:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 10:59:43 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_destroy(t_minishell_p shell)
{
	if (shell)
	{
		ft_split_free(shell->environ);
		//free exec_var;
	}
}
