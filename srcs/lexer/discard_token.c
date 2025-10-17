/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:34:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/17 16:50:16 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_container(t_shell_p shell)
{
	int	i;

	if (!shell->tokens)
		return ;
	if (shell->tokens->tokens)
	{
		i = 0;
		while (i < shell->tokens->tokens_nb)
		{
			discard_token(shell, i);
			i++;
		}
		free(shell->tokens->tokens);
		shell->tokens->tokens = NULL;
	}
	free(shell->tokens);
	shell->tokens = NULL;
}

void	discard_token(t_shell_p shell, int token_index)
{
	if (shell->tokens->tokens[token_index])
	{
		if (shell->tokens->tokens[token_index]->val)
		{
			free(shell->tokens->tokens[token_index]->val);
			shell->tokens->tokens[token_index]->val = NULL;
		}
		free(shell->tokens->tokens[token_index]);
		shell->tokens->tokens[token_index] = NULL;
	}
}
