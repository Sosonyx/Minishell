/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:04:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/09 15:16:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_shell(t_shell_p shell)
{
	if (shell)
	{
		if (shell->ast_root)
			destroy_ast(&shell->ast_root);
		ft_split_free(shell->environ);
		free(shell);
		rl_clear_history();
	}
}
