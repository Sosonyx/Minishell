/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/08 18:31:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_builtin(t_ast_p ast)
{
	char	*cmd;

	if (!ast->leaf->cmds || !ast->leaf->cmds[0]) // si NULL ? jsplus si on l a testee avant
		return (0);
	cmd = ast->leaf->cmds[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (1); //on peut exec ici mais vaut mieux decouper en deux blocs distincts selon moi
	if (ft_strcmp(cmd, "cd") == 0)
		return (1);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (1);
	if (ft_strcmp(cmd, "export") == 0)
		return (1);
	if (ft_strcmp(cmd, "unset") == 0)
		return (1);
	if (ft_strcmp(cmd, "env") == 0)
		return (1);
	if (ft_strcmp(cmd, "exit") == 0)
		return (1);
	return (0);
}

int	execute_builtin(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;

	if (!ast->leaf->cmds || !ast->leaf->cmds[0])
		return (1);
	cmd = ast->leaf->cmds[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(ast->leaf->cmds));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell, &ast->leaf->cmds[1]), 1); // pas prendre la premiere cmd
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell, ast->leaf->cmds), 1);
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(shell->environ), 1);
	// if (ft_strcmp(cmd, "exit") == 0) // exit a revoir
		// return (ft_exit(ast->leaf->cmds, shell));
	return (1);
}


// la table de pid, est allouee pour PID_TABLE_SIZE lignes.
//	La table de pid doit etre resize (+= PID_TABLE_SIZE) lorsqu'elle est pleine 
// aucune prise en compte des pipe et des subshell a ce stade
// en revanche, la priorite fonctionne pour des commandes type celles qui sont dans le fichier parsing_ok.txt

static int	convert_errno(int err)  // convertir le errno vers un code de retour valable
{
	if (err == ENOENT)
		return (127);
	if (err == EACCES || err == EISDIR)
		return (126);
	return (1);
}

static void	execute_fork(t_minishell_p shell, t_ast_p ast)
{
	pid_t	*pid;

	pid = &shell->exec_var.pid_table[shell->exec_var.cur_index];
	*pid = fork();
	if (*pid == 0)
	{
		if (ast->leaf->fds[0] == -1 || ast->leaf->fds[1] == -1)
			exit(convert_errno(ENOENT));
		duplicate_fds(ast->leaf->fds);
		close_fds(ast->leaf->fds);
		execve(*ast->leaf->cmds, ast->leaf->cmds, shell->environ);		// il faut stocker errno pour etre sur qu'il ne change pas entre temps
		print_cmd_error(ast->leaf->command_name, errno);
		exit(convert_errno(errno));
	}
	else
	{
		shell->exec_var.cur_index++;
		close_fds(ast->leaf->fds);
	}
}

int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	char *cmd;

	get_fds(ast, ast->leaf->fds);
	ast->leaf->command_name = ast->leaf->cmds[0];
	cmd = find_cmd(ast->leaf->cmds[0], shell->environ);
	ast->leaf->cmds[0] = cmd;
	if (is_builtin(ast))
		return (execute_builtin(shell, ast));
	execute_fork(shell, ast);
	return (RETURN_OK);
}

//		Je ne comprends pas pourquoi < in cmd > out semble avoir < in qui ne fonctionne pas (write dans 0 et 1, seul 1 fonctionne apres le dup2)