/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_limiter.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/03 15:21:38 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/17 16:35:14 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*expand_limiter(t_shell_p shell, t_redir_p redirs, char *str)
{
	if (ft_strchr(str, '"') || ft_strchr(str, '\''))
	{
		redirs->expand_hd = 1;
		return (remove_quotes_limiter(shell, redirs, str));
	}
	else
		return (_strdup(shell, str));
}
