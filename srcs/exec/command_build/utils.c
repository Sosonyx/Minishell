/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 18:25:30 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/22 17:05:03 by ihadj            ###   ########.fr       */
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

static void	_ft_split_path(t_shell_p shell, char **tab, char *str, char c)
{
	int		i;
	int		j;
	int		start;

	i = -1;
	j = 0;
	start = 0;
	while (1)
	{
		if (str[++i] == c || str[i] == '\0')
		{
			if (i == start)
				tab[j++] = _strdup(shell, "./");
			else
				tab[j++] = malloc_word(shell, &str[start], c);
			if (!tab[j - 1])
			{
				free_tab(tab, j);
				return ;
			}
			if (str[i] == '\0')
				break ;
			start = i + 1;
		}
	}
}

char	**ft_split_path(t_shell_p shell, char **environ, \
	int paths_index, char c)
{
	char	**tab;
	char	*str;

	if (paths_index == -1 || !*(environ[paths_index] + 5))
	{
		tab = _calloc(shell, 2, sizeof(char *));
		*tab = _calloc(shell, 1, sizeof(char));
		return (tab);
	}
	else
		str = environ[paths_index] + 5;
	tab = _calloc(shell, ft_strlen(str) + 2, sizeof(char *));
	if (!tab)
		return (NULL);
	_ft_split_path(shell, tab, str, c);
	return (tab);
}
