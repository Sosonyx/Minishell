/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   addmatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 13:32:58 by fox               #+#    #+#             */
/*   Updated: 2025/10/12 13:34:45 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static char	*set_path(t_shell_p shell, t_wildcard_p wc, char *path)
{
	if (wc->startbydot && !strncmp(path, "./", 2))
	{
		return (remove_quotes(shell, NULL, _strdup(shell, path + 2)));
	}
	else if (!strncmp(path, "//", 2))
	{
		if (wc->isstartdir)
			return (remove_quotes(shell, NULL, _strdup(shell, path + 1)));
		else
			return (remove_quotes(shell, NULL, _strdup(shell, path + 2)));
	}
	else
	{
		return (remove_quotes(shell, NULL, _strdup(shell, path)));
	}
}

static void	matchlist_resize(t_shell_p shell, t_wildcard_p wc)
{
	char	**ptr;

	if (!wc->tmp_matches)
	{
		wc->tmp_matches = _calloc(shell, ++wc->tmp_totalmatches + 1, \
			sizeof(char *));
	}
	else
	{
		wc->tmp_totalmatches++;
		ptr = _realloc(shell, wc->tmp_matches, (wc->tmp_totalmatches) * \
			sizeof(char *), (wc->tmp_totalmatches + 1) * sizeof(char *));
		if (ptr)
			wc->tmp_matches = ptr;
	}
}

void	addmatch(t_shell_p shell, t_wildcard_p wc, char *path)
{
	char	*tmp;

	matchlist_resize(shell, wc);
	if (is_no_abort(shell))
	{
		tmp = set_path(shell, wc, path);
		if (iswildcard(path))
			tmp = remove_quotes(shell, NULL, tmp);
		wc->tmp_matches[wc->tmp_totalmatches - 1] = tmp;
	}
}
