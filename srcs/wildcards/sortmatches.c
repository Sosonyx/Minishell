/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortmatches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:28:41 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 16:31:09 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

void	sortmatches(t_wildcard_p wc)
{
	char	*dupped1;
	char	*dupped2;
	char	*temp;
	int		n;

	n = 1;
	while (n + 1 < wc->totalmatches)
	{
		dupped1 = ft_tolower_str(strdup(wc->matches[n]));
		dupped2 = ft_tolower_str(strdup(wc->matches[n + 1]));
		if (!dupped1 || !dupped2)
		{
			if (dupped1)
				free(dupped1);
			if (dupped2)
				free(dupped2);
			break ;			
		}
		if ((strcmp(dupped1, dupped2) > 0))
		{
			temp = wc->matches[n];
			wc->matches[n] = wc->matches[n + 1];
			wc->matches[n + 1] = temp;
			n = 0;
			if (dupped1)
				free(dupped1);
			if (dupped2)
				free(dupped2);
		}
		else
			n++;
	}
}
