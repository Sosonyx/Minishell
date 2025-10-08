/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_tokens.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/07 18:39:49 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/08 16:49:40 by cgajean          ###   ########.fr       */
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
