/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/10 14:38:56 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

int		execute_ast(t_minishell_p shell, t_ast_p ast);
int		execute_leaf(t_minishell_p shell, t_leaf_p leaf);

void	close_fds(t_leaf_p leaf);

int		wait_children(t_minishell_p shell);
int		get_exit_code(t_minishell_p shell);

bool	is_builtin(t_leaf_p leaf);
int		execute_builtin(t_minishell_p shell, t_leaf_p leaf);

int		extract_return_code(int status);


int		wait_children(t_minishell_p shell);
void	get_redirections(t_leaf_p leaf);

char	*find_cmd(char *cmd, char **env);
void	duplicate_fds(t_leaf_p leaf);

#endif
