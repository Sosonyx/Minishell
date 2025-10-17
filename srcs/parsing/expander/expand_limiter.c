/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:21:38 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/17 14:12:18 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_limiter(t_shell_p shell, t_redir_p redirs, char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
	{
		redirs->expand_hd = 1;
		return (remove_quotes(shell, redirs, str));
	}
	else
		return (_strdup(shell, str));
}
