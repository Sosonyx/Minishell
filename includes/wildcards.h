/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcards.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/21 15:25:25 by fox               #+#    #+#             */
/*   Updated: 2025/09/21 20:26:03 by fox              ###   ########.fr       */
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
	char			*cur_path;
	int				totalmatches;
	int				max_depth;
};

int		iswildcard(char *field);
int		isasterisk(char c);

//	Return 1 if both arguments match, else 0
int		pathmatch(char *ptested, char *pref);

//	Initialize wildcard expansion for the given path
void	wildcard_expand(char ***cmd_args);
void	recdir(t_wildcard_p wc, char *pathopen, int depth);

void	sortmatches(t_wildcard_p wc);

// debug
void	printargs(t_wildcard_p wc);

#endif

