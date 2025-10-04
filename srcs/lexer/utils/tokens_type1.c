/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:08:22 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/04 16:27:12 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' \
		|| c == '(' || c == ')' || c == '&');
}

int	is_word(t_toktype t)
{
	return (t == T_WORD);
}

int	is_redir(t_toktype t)
{
	if (t == T_REDIR_IN || t == T_REDIR_OUT)
		return (1);
	else if (t == T_APPEND || t == T_HEREDOC)
		return (1);
	return (0);
}

int	is_parenth(t_toktype t)
{
	if (t == T_LPARENT)
		return (1);
	if (t == T_RPARENT)
		return (2);
	return (0);
}
