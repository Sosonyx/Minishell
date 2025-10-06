/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:25:30 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/01 15:27:11 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	count_word(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i++] != c)
			count++;
	}
	return (count);
}

static char	*malloc_word(const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = malloc(sizeof(char) * (i + 1));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
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

char	**ft_split_path(char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	if (!str)
		return (NULL);
	tab = malloc(sizeof(char *) * (ft_strlen(str) + 2));
	if (!tab)
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (1)
	{
		if (str[i] == c || str[i] == '\0')
		{
			if (i == start)
				tab[j++] = ft_strdup("./");
			else
				tab[j++] = malloc_word(&str[start], c);
			if (!tab[j - 1])
				return (free_tab(tab, j), NULL);
			if (str[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	tab[j] = NULL;
	return (tab);
}
