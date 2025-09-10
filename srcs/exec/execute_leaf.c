/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/10 12:41:18 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	convert_errno(int err)  // convertir le errno vers un code de retour valable
{
	if (err == ENOENT)
		return (127);
	if (err == EACCES || err == EISDIR)
		return (126);
	return (1);
}

static int	execute_fork(t_minishell_p shell, t_leaf_p leaf)
{
	pid_t	*pid;
	int		errnum;
	int		return_status;

	leaf->pid = fork();
	if (leaf->pid == -1)
	{
		;	// sequence erreur
	}
	if (leaf->pid == 0)
	{
		if (leaf->fds[0] == -1 || leaf->fds[1] == -1)
			exit(convert_errno(ENOENT));
		if (!leaf->treated)
			get_redirections(leaf);
		duplicate_fds(leaf);
		close_fds(leaf);
		execve(*leaf->cmds, leaf->cmds, shell->environ);
		errnum = errno;
		print_cmd_error(leaf->command_name, errnum);
		exit(convert_errno(errnum));
	}
	else
	{
		close_fds(leaf);
		waitpid(leaf->pid, &return_status, 0);
		return (return_status);
	}
}

void	get_command_path(t_minishell_p shell, t_leaf_p leaf)
{
	char *cmd;
	
	leaf->command_name = leaf->cmds[0];
	cmd = find_cmd(leaf->cmds[0], shell->environ);
	if (cmd)
		leaf->cmds[0] = cmd;
}

int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	char *cmd;
	int	return_status;

	// get_redirections(ast->leaf, NULL);
	close_fds(ast->leaf);
	get_command_path(shell, ast->leaf);
	if (is_builtin(ast))
		return_status = execute_builtin(shell, ast);
	else
		return_status = execute_fork(shell, ast->leaf);
	return (return_status);
}
