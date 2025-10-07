/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

# define IS_VALID_FD > 2

/********************************************************************************/
/*  	Builtins                       											*/
/********************************************************************************/

char		*ft_getcwd(char **env);

int			ft_echo(t_shell_p shell, char **args);
int			ft_pwd(t_shell_p shell, char **args);
int			ft_cd(t_shell_p shell, char **args);
int			ft_exit(t_shell_p shell, char **args);
int			ft_export(t_shell_p shell, char **args_to_add);
int			ft_unset(t_shell_p shell, char **args);
int			ft_env(t_shell_p shell, char **args);

/********************************************************************************/
/*		Execute                        											*/
/********************************************************************************/

void		execute_ast(t_shell_p shell, t_ast_p *ast);
void		_execute_ast(t_shell_p shell, t_ast_p ast);
void		execute_subshell(t_shell_p shell, t_ast_p ast);
void		execute_pipe(t_shell_p shell, t_ast_p ast);
void		execute_and(t_shell_p shell, t_ast_p ast);
void		execute_or(t_shell_p shell, t_ast_p ast);
void		execute_leaf(t_shell_p shell, t_ast_p ast);
void		execute_builtin(t_shell_p shell, t_ast_p ast);

	///
	///	misc exec
	///
void		wait_if_leaf(t_leaf_p leaf, int *rstatus);
int			extract_return_code(int status);
int			convert_errno(int err);

// char	*find_cmd(char *cmd, char **env);
char		*find_cmd(t_shell_p shell, t_ast_p ast);

bool		is_builtin(t_leaf_p leaf);

void		preconfig_leaf(t_shell_p shell, t_ast_p ast);
char		**ft_split_path(char *str, char c);

/********************************************************************************/
/*		Files & redirections              										*/
/********************************************************************************/

void		input_heredoc(t_shell_p shell, t_leaf_p leaf);
void		forward_fds(t_ast_p ast);
void		save_std_fileno(t_shell_p shell);
void		restore_std_fileno(t_shell_p shell, t_ast_p ast);
int			redirect_leaf(t_shell_p shell, t_ast_p ast);
int			open_files(t_shell_p shell, t_leaf_p leaf, t_redir_p cur_redir);
void		close_fds(t_ast_p ast, int mode);
void		close_secure(int *fd);
void		safe_dup2(int oldfd, int newfd);

#endif
