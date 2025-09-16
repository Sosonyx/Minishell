/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/16 20:22:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

int		execute_ast(t_minishell_p shell, t_ast_p ast);
int		_execute_ast(t_minishell_p shell, t_ast_p ast);

int 	execute_subshell(t_minishell_p shell, t_ast_p ast);
int 	execute_pipe(t_minishell_p shell, t_ast_p ast);
int 	execute_and(t_minishell_p shell, t_ast_p ast);
int 	execute_or(t_minishell_p shell, t_ast_p ast);
void	execute_leaf(t_minishell_p shell, t_ast_p ast);
int		execute_builtin(t_minishell_p shell, t_leaf_p leaf);
void	wait_if_leaf(t_leaf_p leaf, int *rstatus);


void	forward_fds(t_ast_p ast);

void	close_fds(t_ast_p ast, int mode);
void	close_secure(int *fd);



bool	is_builtin(t_leaf_p leaf);

void	preconfig_leaf(t_minishell_p shell, t_leaf_p leaf);

char	*find_cmd(char *cmd, char **env);
int		redirect_leaf(t_ast_p ast);

int		extract_return_code(int status);

#endif
