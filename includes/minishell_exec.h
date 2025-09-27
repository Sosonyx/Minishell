/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/26 11:02:21 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

# define IS_VALID_FD > 2

/********************************************************************************/
/*  	Builtins                       											*/
/********************************************************************************/

int	    	ft_echo(t_minishell_p shell, char **args);
int			ft_pwd(t_minishell_p shell, char **args);
int	    	ft_cd(t_minishell_p shell, char **args);
int			ft_exit(t_minishell_p shell, char **args);
int	    	ft_export(t_minishell_p shell, char **args_to_add);
int	    	ft_unset(t_minishell_p shell, char **args);
int	    	ft_env(t_minishell_p shell, char **args);

/********************************************************************************/
/*		Execute                        											*/
/********************************************************************************/

int		execute_ast(t_minishell_p shell, t_ast_p *ast);
int		_execute_ast(t_minishell_p shell, t_ast_p ast);

int 	execute_subshell(t_minishell_p shell, t_ast_p ast);
int 	execute_pipe(t_minishell_p shell, t_ast_p ast);
int 	execute_and(t_minishell_p shell, t_ast_p ast);
int 	execute_or(t_minishell_p shell, t_ast_p ast);
int 	execute_leaf(t_minishell_p shell, t_ast_p ast);
void	execute_builtin(t_minishell_p shell, t_ast_p ast);

	///
	///	misc exec
	///
		
void	wait_if_leaf(t_leaf_p leaf, int *rstatus);
int		extract_return_code(int status);

char	*find_cmd(char *cmd, char **env);
bool	is_builtin(t_leaf_p leaf);

void	preconfig_leaf(t_minishell_p shell, t_leaf_p leaf);


/********************************************************************************/
/*		Files & redirections              										*/
/********************************************************************************/

void	input_heredoc(t_minishell_p shell, t_leaf_p leaf);

void	forward_fds(t_ast_p ast);

void    save_std_fileno(t_minishell_p shell);
void    restore_std_fileno(t_minishell_p shell, t_ast_p ast);

int		redirect_leaf(t_minishell_p shell, t_ast_p ast);

void	close_fds(t_ast_p ast, int mode);
void	close_secure(int *fd);

#endif
