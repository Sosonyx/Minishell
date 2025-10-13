/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:34:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/13 18:36:22 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens_container(t_shell_p shell, t_tok_container *t)
{
	int	i;

	if (!t)
		return ;
	if (t->tokens)
	{
		i = 0;
		while (i < t->tokens_nb)
		{
			discard_token(shell, i);
			i++;
		}
		free(t->tokens);
	}
	free(t);
}

void	discard_token(t_shell_p shell, int token_index)
{
	if (shell->tokens->tokens[token_index])
	{
		free(shell->tokens->tokens[token_index]->val);
		free(shell->tokens->tokens[token_index]);
		shell->tokens->tokens[token_index] = NULL;
	}
}
