/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 18:43:32 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(void)
{
	return (0);
}

void	execute_builtin(void)
{
	return ;
}

//	La table de pid doit etre resize (+= PID_TABLE_SIZE) lorsqu'elle est pleine 
static void	execute_fork(t_minishell_p shell,t_ast_p ast)
{
	pid_t	*pid;

	pid = &shell->exec_var.pid_table[shell->exec_var.cur_index];
	*pid = fork();
	if (*pid == 0)
	{
		execve(*ast->leaf->cmds, ast->leaf->cmds, shell->environ);
		exit(errno);
	}
	else
		shell->exec_var.cur_index++;
}

int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	if (is_builtin())
		execute_builtin();
	else
		execute_fork(shell, ast);
	return (1);

	// extraction du code d'erreur a faire
}
