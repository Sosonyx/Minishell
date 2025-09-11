/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/11 14:25:46 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

int		execute_ast(t_minishell_p shell, t_ast_p ast);

int 	execute_subshell(t_minishell_p shell, t_ast_p ast);
int 	execute_pipe(t_minishell_p shell, t_ast_p ast);
int 	execute_and(t_minishell_p shell, t_ast_p ast);
int 	execute_or(t_minishell_p shell, t_ast_p ast);
int		execute_leaf(t_minishell_p shell, t_leaf_p leaf);
int		execute_builtin(t_minishell_p shell, t_leaf_p leaf);

void	close_fds(t_leaf_p leaf);

bool	is_builtin(t_leaf_p leaf);

void	configure_leaf(t_minishell_p shell, t_leaf_p leaf);

char	*find_cmd(char *cmd, char **env);
int		redirect_leaf(t_leaf_p leaf);

int		extract_return_code(int status);

#endif
