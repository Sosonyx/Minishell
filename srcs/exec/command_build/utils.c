/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:25:30 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/12 13:26:09 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*malloc_word(t_shell_p shell, const char *str, char c)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	word = _calloc(shell, i + 1, sizeof(char));
	if (!word)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		word[i] = str[i];
		i++;
	}
	return (word);
}

static void	free_tab(char **tab, int index)
{
	while (--index >= 0)
		free(tab[index]);
	free(tab);
}

char	**ft_split_path(t_shell_p shell, char *str, char c)
{
	char	**tab;
	int		i;
	int		j;
	int		start;

	if (!str)
		return (NULL);
	tab = _calloc(shell, ft_strlen(str) + 2, sizeof(char *));
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
				tab[j++] = _strdup(shell, "./");
			else
				tab[j++] = malloc_word(shell, &str[start], c);
			if (!tab[j - 1])
				return (free_tab(tab, j), NULL);
			if (str[i] == '\0')
				break ;
			start = i + 1;
		}
		i++;
	}
	return (tab);
}
