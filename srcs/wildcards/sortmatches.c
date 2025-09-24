/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sortmatches.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 17:28:41 by fox               #+#    #+#             */
/*   Updated: 2025/09/24 13:37:24 by fox              ###   ########.fr       */
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
	
	diff_nocase = strcmp_nocase(s1, s2);
	if (diff_nocase)
		return (diff_nocase);
	else
		return (-ft_strcmp(s1, s2));
}

static void	_swap(char **s1, char **s2)
{
	char	*temp;
	
	temp = *s1;
	*s1 = *s2;
	*s2 = temp;
}

void	sortmatches(t_wildcard_p wc)
{
	int		n;

	n = 0;
	while (n + 1 < wc->tmp_totalmatches)
	{
		if (_compare(wc->tmp_matches[n], wc->tmp_matches[n + 1]) > 0)
		{
			_swap(&wc->tmp_matches[n], &wc->tmp_matches[n + 1]);
			n = 0;
		}
		else
			n++;
	}
}
