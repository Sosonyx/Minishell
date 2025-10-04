/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_parsing.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/04 16:36:03 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_PARSING_H
# define MINISHELL_PARSING_H

# include "minishell.h"


/********************************************************************************/
/*  Environment / arrays / utils											    */
/********************************************************************************/

void		free_array(char **array);
char		**dup_env(char **envp);
int			get_array_size(char **arr);

int			is_valid_number(char *str);
long long	ft_atol(const char *nptr);
int			ft_strcmp(const char *s1, const char *s2);
void		ft_split_free(char **arr);

/********************************************************************************/
/*  Lexer                       											    */
/********************************************************************************/

int			is_special(char c);
int			special_len(const char *line, int i);
int			is_pipe(t_toktype t);
int			is_redir(t_toktype t);
int			is_parenth(t_toktype t);
int			is_word(t_toktype t);
int			is_control_op(t_toktype t);
int			_is_word(t_toktype cur, t_token **toks, int i);
int			_lparenth(t_toktype cur, t_token **toks, int i);
int			_redir(t_toktype cur, t_token **toks, int i);
int			_control_op(t_toktype cur, t_token **toks, int i);

void		syntax_err(const char *near);
int			check_syntax(t_token **toks);

t_token		*create_token(char *val, t_toktype type, bool sq, bool dq);
t_toktype	get_token_type(const char *line);
int			count_tokens(char *line);
int			stock_word(t_token **arr, int j, char *line, int *i);
int			stock_quoted(t_token **arr, int j, char *line, int *i);
int			stock_special(t_token **arr, int j, char *line, int *i);
int			stock_tokens(t_tok_container *a, char *line);
int			tokenize_input(t_minishell_p shell, int *g_sigstatus);

/********************************************************************************/
/*  Parsing / AST                      										    */
/********************************************************************************/

int			parse_tokens(t_minishell_p shell, t_ast_p *ast);
void		build_ast(t_minishell_p shell, t_ast_p *ast, t_build_var vars);

// t_redir_p	build_redir(t_minishell_p shell, t_build_var vars);
int			build_redir(t_minishell_p shell, t_ast_p ast, t_build_var vars);
int			build_cmd(t_minishell_p shell, t_ast_p ast, t_build_var vars);

int			parse_cntl_and_or(t_minishell_p shell, t_ast_p *op, t_build_var vars);
int			parse_cntl_pipe(t_minishell_p shell, t_ast_p *op, t_build_var vars);
int			parse_subshell(t_minishell_p shell, t_ast_p *op, t_build_var vars);
int			create_cntl_op(t_minishell_p shell, t_ast_p *op, t_toktype type);
int			create_leaf(t_minishell_p shell, t_ast_p *ast, t_build_var vars);

void		discard_token(t_minishell_p shell, int token_index);

void		destroy_ast(t_ast_p *ast);
void		destroy_leaf(t_ast_p ast);
void		destroy_redir(t_ast_p ast);

int			init_global_end(t_build_var vars, t_tok_container_p tok_container);
int			set_global_end(t_build_var vars, t_tok_container_p tok_container);
int			set_left_end(int start, int op_pos, t_tok_container_p tok_container);
int			set_right_end(int op_pos, int end, t_tok_container_p tok_container, int *right_start);


/********************************************************************************/
/*  Expand                            										    */
/********************************************************************************/

void		pipeline_expand(t_minishell *shell, t_ast_p ast);
t_expanded	expand_command(t_minishell *shell, char *str);
char		*get_env_value(t_minishell *shell, char *name);
char		*expand_limiter(t_redir_p redir, char *str);
char		*append_char(char *str, char c);

#endif