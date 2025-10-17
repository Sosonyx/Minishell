/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aggregate_matches.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:01:17 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/17 14:11:24 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	aggregate_matches(t_shell_p shell, t_wildcard_p wc, char *args)
{
	char	**matches;

	matches = _calloc(shell, wc->totalmatches + \
		wc->tmp_totalmatches + 2, sizeof(char *));
	if (!matches)
		return ;
	ft_memcpy(matches, wc->matches, wc->totalmatches * sizeof(char *));
	if (wc->tmp_matches)
	{
		ft_memcpy(matches + wc->totalmatches, \
			wc->tmp_matches, wc->tmp_totalmatches * sizeof(char *));
		free(wc->tmp_matches);
		wc->tmp_matches = NULL;
		wc->totalmatches += wc->tmp_totalmatches;
		wc->tmp_totalmatches = 0;
	}
	else
	{
		matches[wc->totalmatches] = remove_quotes(shell, \
			NULL, _strdup(shell, args));
		++wc->totalmatches;
	}
	free(wc->matches);
	wc->matches = matches;
}
