/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 19:00:31 by cgajean          ###   ########.fr       */
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

// la table de pid, est allouee pour PID_TABLE_SIZE lignes.
//	La table de pid doit etre resize (+= PID_TABLE_SIZE) lorsqu'elle est pleine 

// aucune prise en compte des pipe et des subshell a ce stade

// en revanche, la priorite fonctionne pour des commandes type celles qui sont dans le fichier parsing_ok.txt

static void	execute_fork(t_minishell_p shell, t_ast_p ast)
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

// tres basique, permet juste de visualiser l'execution de commandes simples
int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	if (is_builtin())
		execute_builtin();
	else
		execute_fork(shell, ast);
	return (1);

	// extraction du code d'erreur a faire
}
