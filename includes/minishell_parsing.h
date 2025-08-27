/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/27 17:30:03 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"

// BUILT-IN
int			ft_cd(char *path, char **env);
char		*ft_getcwd(char **env);
// int			ft_exit(char **option, t_ms	exit_code);

// UTILS
int			is_valid_number(char *str);
long long	ft_atol(const char *nptr);

// LEXER# include "minishell_data.h"
t_token		*create_token(char *val, t_toktype type, bool sq, bool dq);
t_toktype	get_token_type(const char *line);
int			count_tokens(char *line);
int			stock_word(t_token **arr, int j, char *line, int *i);
int			stock_quoted(t_token **arr, int j, char *line, int *i);
int			stock_special(t_token **arr, int j, char *line, int *i);
int			stock_tokens(t_arg *a, char *line);
// int			stock_parenth(t_token **tokens, int j, const char *line, int *i);

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
