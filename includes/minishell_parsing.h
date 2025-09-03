/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/03 14:55:20 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"

/********************************************************************************/
/*			Builtins															*/
/********************************************************************************/
int			ft_cd(char *path, char **env);
char		*ft_getcwd(char **env);
// int			ft_exit(char **option, t_ms	exit_code);

/********************************************************************************/
/*			Utils																*/
/********************************************************************************/
int			is_valid_number(char *str);
long long	ft_atol(const char *nptr);

/********************************************************************************/
/*			Lexer																*/
/********************************************************************************/
t_token		*create_token(char *val, t_toktype type, bool sq, bool dq);
t_toktype	get_token_type(const char *line);
int			count_tokens(char *line);
int			stock_word(t_token **arr, int j, char *line, int *i);
int			stock_quoted(t_token **arr, int j, char *line, int *i);
int			stock_special(t_token **arr, int j, char *line, int *i);
int			stock_tokens(t_tok_container *a, char *line);
// int			stock_parenth(t_token **tokens, int j, const char *line, int *i);

/********************************************************************************/
/*			Parsing																*/
/********************************************************************************/
int			check_syntax(t_token **toks);
char		*ft_strndup(const char *s, size_t len);
int			count_word(const char *str, char c);
char		*ft_strcat(char *dest, const char *src);
// int			is_blank_line(const char *s);
int			ft_isspace(int c);
int			is_special(char c);
int			special_len(const char *line, int i);
int			is_pipe(t_toktype t);
int			is_redir(t_toktype t);
int			is_parenth(t_toktype t);


/********************************************************************************/
/*			Parsing																*/
/********************************************************************************/

// t_ast_p		parse_tokens(t_ast_p ast, t_tok_container_p tok_container);
t_error_status		parse_tokens(t_ast_p *ast, t_tok_container_p tok_container);

	/*		find_external_functions.c		*/
t_error_status	find_external_parenthesis(t_ast_p *op, t_tok_container_p tok_container);
t_error_status	find_external_cntl_pipe(t_ast_p *op, t_tok_container_p tok_container, int start, int end);
t_error_status	find_external_cntl_and_or(t_ast_p *op, t_tok_container_p tok_container, int start, int end);

t_error_status	create_leaf(t_ast_p *ast, t_tok_container_p tok_container, int i);


/* t_error_status	build_cmd(char **cmd, t_tok_container_p tok_container, int i);
t_redir_p build_redir(t_tok_container_p tok_container, int i); */

#endif
