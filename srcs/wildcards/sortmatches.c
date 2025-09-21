/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortmatches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:28:41 by fox               #+#    #+#             */
/*   Updated: 2025/09/21 19:45:28 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

void	sortmatches(t_wildcard_p wc)
{
	char	*temp;
	int		n;

	n = 1;
	while (n + 1 < wc->totalmatches)
	{
		if (strcmp(wc->matches[n], wc->matches[n + 1]) > 0)
		{
			temp = wc->matches[n];
			wc->matches[n] = wc->matches[n + 1];
			wc->matches[n + 1] = temp;
			n = 0;
		}
		else
			n++;
	}
}
