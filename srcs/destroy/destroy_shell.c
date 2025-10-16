/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_shell.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 10:04:56 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/16 18:03:45 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_shell(t_shell_p shell)
{
	if (shell)
	{
		if (shell->ast_root)
			destroy_ast(&shell->ast_root);
		if (shell->tokens)
			free_tokens_container(shell, shell->tokens);
		free(shell->input);
		ft_split_free(shell->environ);
		free(shell);
		rl_clear_history();
	}
}
