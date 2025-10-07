/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:00:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_input(t_shell_p shell, int *g_sigstatus)
{
	shell->tokens = ft_calloc(1, sizeof(struct s_tok_container));
	if (shell->tokens)
	{
		if (!stock_tokens(shell->tokens, shell->input) || \
			!check_syntax((shell->tokens)->tokens))
		{
			free(shell->tokens);
			shell->tokens = NULL;
			return (RETURN_FAIL);
		}
		else
			return (RETURN_OK);
	}
	else
	{
		return (RETURN_FAIL);
	}
}
