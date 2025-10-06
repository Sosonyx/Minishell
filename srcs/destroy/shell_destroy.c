/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_destroy.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:04:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/25 10:42:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_destroy(t_minishell_p shell)
{
	if (shell)
	{
		ft_split_free(shell->environ);
		free(shell);
	}
}
