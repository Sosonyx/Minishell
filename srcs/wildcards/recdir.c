/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recdir.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 18:16:52 by fox               #+#    #+#             */
/*   Updated: 2025/09/21 19:36:51 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

static int	skipitem(char *dir, char *field)
{
	if (field && iswildcard(field) && !iswildcard(field + 1))
	{
		return (!(strcmp(".", dir) && strcmp("..", dir)));
	}
	else
		return (0);
}

static char *catpath(char *pathopen, char *added)
{
	char	*new_path;
	char	*temp;
	
	new_path = ft_strjoin(pathopen, "/");
	if (new_path)
		temp = new_path;
	new_path = ft_strjoin(new_path, added);
	free(temp);
	return (new_path);
}

void	savepath(t_wildcard_p wc, struct dirent *sdir, char *pathopen)
{
	char	**ptr;
	char	*tmp;
	
	if (strcmp(DOT_ENTRY, sdir->d_name) && strcmp(DOTDOT_ENTRY, sdir->d_name))
	{
		if (!wc->matches)
			wc->matches = calloc(++(wc->totalmatches), sizeof(char *));
		else
		{
			ptr = realloc(wc->matches, ++(wc->totalmatches) * sizeof(char *));
			if (ptr)
				wc->matches = ptr;
		}				
		pathopen = catpath(pathopen, sdir->d_name);
		if (pathopen)
		{
			wc->matches[wc->totalmatches - 1] = strdup(pathopen);
		}
		else
		{
			print_generic_error(NULL, MEM_ERRMSG);
		}
	}
}

static void	_recdir(t_wildcard_p wc, struct dirent *sdir, char *pathopen, int depth)
{
	char	*path = NULL;
	
	if (!skipitem(sdir->d_name, wc->spath[depth]) && pathmatch(sdir->d_name, wc->spath[depth]))
	{
		path = catpath(pathopen, sdir->d_name);
		recdir(wc, path, depth + 1);
		free(path);
	}	
}

void	recdir(t_wildcard_p wc, char *pathopen, int depth)
{
	DIR				*dirp;
	struct dirent	*sdir;
	
	dirp = NULL;
	if (pathopen)
		dirp = opendir(pathopen);
	if (dirp)
	{
		sdir = readdir(dirp);
		while (sdir)
		{
			if (depth < wc->max_depth)
			{
				_recdir(wc, sdir, pathopen, depth);
			}
			else
			{
				savepath(wc, sdir, pathopen);
			}
			sdir = readdir(dirp);
		}
		closedir(dirp);
	}
}
