/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:39:49 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/17 16:46:04 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_tokens(t_shell_p shell)
{
	if (shell->tokens->tokens)
		free(shell->tokens->tokens);
	shell->tokens->tokens = NULL;
	if (shell->tokens)
		free(shell->tokens);
	shell->tokens = NULL;
}
