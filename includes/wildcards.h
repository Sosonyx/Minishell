/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:25:25 by fox               #+#    #+#             */
/*   Updated: 2025/09/30 20:17:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARDS_H
# define WILDCARDS_H

# include "minishell.h"

# define DOT_ENTRY "."
# define DOTDOT_ENTRY ".."

typedef struct s_wildcard *t_wildcard_p;

struct s_wildcard
{
	char			**spath;
	char			**matches;
	char			**tmp_matches;
	char			*cur_path;
	int				totalmatches;
	int				tmp_totalmatches;
	int				max_depth;
	bool			lastisdir;
	bool			startbydot;
	bool			isstartdir;
};

struct s_pathmatch
{
	char			*start_sequence;
	char			*end_sequence;
};

typedef struct s_path t_path;
typedef t_path *t_path_p;

int		iswildcard(char *field);
int		isasterisk(char c);
int		isdotdotdotentry(char *dir);
int		skipdotdotdot(char *dir, char *field);
bool	ishidden(char *dir);
char 	*catpath(char *pathopen, char *added);
int 	strncmprev(const char *s1, const char *s2, int size);
bool	islastsequence(char *field);

void	wildcard_expand(t_minishell_p shell, t_ast_p ast);

int		pathmatch(char *ptested, char *pref);
void	recdir(t_wildcard_p wc, char *pathopen, int depth);
void	savepath(t_wildcard_p wc, struct dirent *sdir, char *path, int depth);
void	addmatch(t_wildcard_p wc, char *path);
void	sortmatches(t_wildcard_p wc);

#endif
