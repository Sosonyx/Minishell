/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:08:22 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/05 13:20:58 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_special(char c)
{
	return (c == '|' || c == '<' || c == '>' \
		|| c == '(' || c == ')' || c == '&');
}

int	is_pipe(t_toktype t)
{
	return (t == T_PIPE);
}

int	is_redir(t_toktype t)
{
	return (t == T_REDIR_IN || t == T_REDIR_OUT || t == T_APPEND || t == T_HEREDOC);
}

int	is_parenth(t_toktype t)
{
	return (t == T_LPARENT || t == T_RPARENT);
}

int	is_control_op(t_toktype t)
{
	return ((is_redir(t) || is_pipe(t) || is_parenth(t)));
}
