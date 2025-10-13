/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:39:49 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/13 18:29:26 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	destroy_tokens(t_shell_p shell)
{
	free(shell->tokens->tokens);
	shell->tokens->tokens = NULL;
	free(shell->tokens);
	shell->tokens = NULL;
}
