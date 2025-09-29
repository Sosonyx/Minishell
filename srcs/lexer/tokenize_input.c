/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:00:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 10:23:54 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* t_tok_container_p	tokenize_input(char *input, t_tok_container_p *tok_container, int *g_status)
{
	*tok_container = ft_calloc(1, sizeof(struct s_tok_container));
	if (*tok_container)
	{
		if (!stock_tokens(*tok_container, input) || !check_syntax((*tok_container)->tokens))
		{
			*g_status = 258;
			// syntax error
			free(*tok_container);		// pour rappel de free, mais une fonction est a creer
			*tok_container = NULL;
		}
	}
	else
	{
		// tokenization error -> close ou message d'erreur et nouveau prompt ?
	}
	return (*tok_container);
}
 */

 int	tokenize_input(t_minishell_p shell, int *g_status)
{
	shell->tokens = ft_calloc(1, sizeof(struct s_tok_container));
	if (shell->tokens)
	{
		if (!stock_tokens(shell->tokens, shell->input) || !check_syntax((shell->tokens)->tokens))
		{
			// si stock fonctionne mais check echoue, il faut vider tokens
			// la fonction free() ci-dessous est pour rappel 
			
			*g_status = 258;
			// syntax error
			free(shell->tokens);	// pour rappel
			shell->tokens = NULL;
			return (RETURN_FAIL);
		}
		else
			return (RETURN_OK);
	}
	else
	{
		// tokenization error -> close ou message d'erreur et nouveau prompt ?
		return (RETURN_FAIL);
	}	
}
