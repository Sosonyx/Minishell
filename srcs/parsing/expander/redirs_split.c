/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 13:21:21 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/22 13:21:49 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_ws.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:40:17 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/22 17:40:17 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_ws(char c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

static int	count_word(const char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] && is_ws(s[i]))
		i++;
	while (s[i])
	{
		if (!is_ws(s[i]))
		{
			count++;
			while (s[i] && !is_ws(s[i]))
				i++;
		}
		while (s[i] && is_ws(s[i]))
			i++;
	}
	return (count);
}

static char	*malloc_word(const char *s)
{
	int		i;
	char	*word;

	i = 0;
	while (s[i] && !is_ws(s[i]))
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (s[i] && !is_ws(s[i]))
	{
		word[i] = s[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static void	free_tab(char **tab, int index)
{
	while (--index >= 0)
		free(tab[index]);
	free(tab);
}

char	**ft_split_ws(char const *s)
{
	char	**tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_word(s) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		if (!is_ws(s[i]))
		{
			tab[j++] = malloc_word(&s[i]);
			if (!tab[j - 1])
				return (free_tab(tab, j), NULL);
			while (s[i] && !is_ws(s[i]))
				i++;
		}
		else
			i++;
	}
	return (tab[j] = NULL, tab);
}
