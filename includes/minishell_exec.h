/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/08 18:17:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_EXEC_H
# define MINISHELL_EXEC_H

# include "minishell.h"

int		execute_ast(t_minishell_p shell, t_ast_p ast);
int		execute_leaf(t_minishell_p shell, t_ast_p ast);

void	close_fds(int fds[2]);

int		wait_children(t_minishell_p shell);
int		get_exit_code(t_minishell_p shell);

#endif
