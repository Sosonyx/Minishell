/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/09 15:22:10 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

int		execute_ast(t_minishell_p shell, t_ast_p ast);
int		execute_leaf(t_minishell_p shell, t_ast_p ast);

void	close_fds(t_leaf_p leaf);

int		wait_children(t_minishell_p shell);
int		get_exit_code(t_minishell_p shell);

bool	is_builtin(t_ast_p ast);
int		execute_builtin(t_minishell_p shell, t_ast_p ast);

int		extract_return_code(int *status);


int				wait_children(t_minishell_p shell);
void			get_redirections(t_leaf_p leaf, int pipe[2]);

// t_return_status	exec_ast(t_ast_p ast, t_ast_branch branch);
char			*find_cmd(char *cmd, char **env);
void			duplicate_fds(int fds[2]);

#endif
