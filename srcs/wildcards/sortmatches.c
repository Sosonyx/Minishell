/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortmatches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:28:41 by fox               #+#    #+#             */
/*   Updated: 2025/09/24 12:19:06 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	strcmp_nocase(const char *s1, const char *s2)
{
	int	diff;
	
    while (s1 && s2 && *s1 && *s2)
    {
		diff = ft_tolower(*s1) - (ft_tolower(*s2));
		if (diff)
			break ;
        s1++;
        s2++;
    }
    return (diff);
}

static int	_compare(const char *s1, const char *s2)
{
	int	diff_nocase;
	int	diff_wcase;

	diff_nocase = strcmp_nocase(s1, s2);
	diff_wcase = ft_strcmp(s1, s2);
	if (diff_nocase)
		return (diff_nocase);
	else
		return (-diff_wcase);
}

void	sortmatches(t_wildcard_p wc)
{
	char	*temp;
	int		n;

	n = 1;
	while (n + 1 < wc->totalmatches)
	{
		if (_compare(wc->matches[n], wc->matches[n + 1]) > 0)
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
