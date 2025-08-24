/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/24 18:51:42 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <unistd.h>
# include <sys/stat.h>
# include <signal.h>
# include "libft.h"

typedef enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_LPARENT,
	T_RPARENT
}	t_toktype;

typedef enum e_redirtype
{ 
	R_IN,
	R_OUT,
	R_APP,
	R_HDOC
}	t_redirtype;

typedef struct s_token
{
	t_toktype	type;
	char		*val;
	bool		was_single_quoted; // pour heredoc (si delim etait quote)
	bool		was_double_quoted; // on autorise l expansion
	bool		was_in_parenth;
}	t_token;

typedef struct s_arg
{
	t_token	**cmds;
	char	**args;
	int		oldfd[2];
	int		nextfd[2];
	int		ac;
}	t_arg;

// BUILT-IN
int			ft_cd(char *path, char **env);
char		*ft_getcwd(char **env);
// int			ft_exit(char **option, t_ms	exit_code);

// UTILS
int			is_valid_number(char *str);
long long	ft_atol(const char *nptr);

// LEXER
t_token		*create_token(char *val, t_toktype type, bool sq, bool dq);
t_toktype	get_token_type(const char *line);
int			count_tokens(char *line);
int			stock_word(t_token **arr, int j, const char *line, int *i);
int			stock_quoted(t_token **arr, int j, const char *line, int *i);
int			stock_special(t_token **arr, int j, const char *line, int *i);
int			stock_tokens(t_arg *a, char *line);

// PARSING
int			check_syntax(t_token **toks);
char		*ft_strndup(const char *s, size_t len);
int			count_word(const char *str, char c);
char		*ft_strcat(char *dest, const char *src);
int			is_blank_line(const char *s);
int			ft_isspace(int c);
int			is_special(char c);
int			special_len(const char *line, int i);

#endif