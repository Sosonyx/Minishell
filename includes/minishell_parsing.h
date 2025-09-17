/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/17 15:27:04 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"

/********************************************************************************/
/*			Builtins															*/
/********************************************************************************/
int				ft_echo(char **args);
int				ft_pwd(void);
int				ft_cd(t_minishell *shell, char **args);
int				ft_exit(char **args, int last_status);
int				ft_export(t_minishell *shell, char **args_to_add);
int				ft_unset(t_minishell *shell, char **args);
int				ft_env(char **env);

void			free_array(char **array);
char			**dup_env(char **envp);
int				get_array_size(char **arr);


// int			ft_exit(char **option, t_ms	exit_code);

/********************************************************************************/
/*			Utils																*/
/********************************************************************************/
int				is_valid_number(char *str);
long long		ft_atol(const char *nptr);
int	ft_strcmp(const char *s1, const char *s2);

/********************************************************************************/
/*			Lexer																*/
/********************************************************************************/
t_token			*create_token(char *val, t_toktype type, bool sq, bool dq);
t_toktype		get_token_type(const char *line);
int				count_tokens(char *line);
int				stock_word(t_token **arr, int j, char *line, int *i);
int				stock_quoted(t_token **arr, int j, char *line, int *i);
int				stock_special(t_token **arr, int j, char *line, int *i);
int				stock_tokens(t_tok_container *a, char *line);
// int			stock_parenth(t_token **tokens, int j, const char *line, int *i);
t_tok_container_p	tokenize_input(char *input, t_tok_container_p *tok_container, int *g_status);
void			destroy_tok_container(t_tok_container_p tok_container);


/********************************************************************************/
/*			Parsing																*/
/********************************************************************************/
int				check_syntax(t_token **toks);
char			*ft_strndup(const char *s, size_t len);
// int				count_word(const char *str, char c);
char			*ft_strcat(char *dest, const char *src);
// int			is_blank_line(const char *s);
int				ft_isspace(int c);
int				is_special(char c);
int				special_len(const char *line, int i);
int				is_pipe(t_toktype t);
int				is_redir(t_toktype t);
int				is_parenth(t_toktype t);
int				is_control_op(t_toktype t);


/********************************************************************************/
/*			Parsing																*/
/********************************************************************************/

int				parse_tokens(t_ast_p *ast, t_tok_container_p tok_container);
void			build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, t_ast_branch branch, int first);
t_redir_p		build_redir(t_tok_container_p tok_container, int i, int end);
int				build_cmd(char ***cmd, t_tok_container_p tok_container, int start, int end);
void			destroy_ast(t_ast_p *ast);

int				parse_cntl_and_or(t_ast_p *op, t_tok_container_p tok_container, int start, int end);
int				parse_cntl_pipe(t_ast_p *op, t_tok_container_p tok_container, int start, int end);
int				parse_subshell(t_ast_p *op, t_tok_container_p tok_container, int start, int end);

// int	build_cmd(char ***cmd, t_tok_container_p tok_container, int i);
// t_redir_p 		build_redir(t_tok_container_p tok_container, int i);
int				create_leaf(t_ast_p *ast, t_tok_container_p tok_container, int start, int end);


#endif
