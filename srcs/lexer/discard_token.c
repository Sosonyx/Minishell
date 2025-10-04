/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:34:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 12:35:05 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	discard_token(t_minishell_p shell, int token_index)
{
	if (shell->tokens->tokens[token_index])
	{
		free(shell->tokens->tokens[token_index]->val);
		free(shell->tokens->tokens[token_index]);
		shell->tokens->tokens[token_index] = NULL;
	}
}
