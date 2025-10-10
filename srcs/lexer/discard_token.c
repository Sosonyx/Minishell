/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   discard_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:34:53 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/10 22:25:07 by sosony           ###   ########.fr       */
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
		while (t->tokens[i])
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
