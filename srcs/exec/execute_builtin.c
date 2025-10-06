/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:10 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/06 16:25:54 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_leaf_p leaf)
{
	char	*cmd;

	if (!leaf->cmds || !leaf->cmds[0])
		return (false);
	cmd = leaf->cmds[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

static int	execute_command(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;

	cmd = ast->leaf->cmds[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell, &ast->leaf->cmds[1]));
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "exit") == 0)
		return (ft_exit(shell, ast->leaf->cmds));
	else
		return (EXIT_FAILURE);
}

void	execute_nofork(t_minishell_p shell, t_ast_p ast)
{
	save_std_fileno(shell);
	if (redirect_leaf(shell, ast) == -1)
	{
		shell->exit_code = -1;
		restore_std_fileno(shell, ast);
		return ;
	}
	if (ast->leaf->abort == false)
	{
		shell->exit_code = execute_command(shell, ast);
	}
	else
	{
		shell->exit_code = ERRVAL1;
	}
	restore_std_fileno(shell, ast);
}

void	execute_wfork(t_minishell_p shell, t_ast_p ast)
{
	ast->leaf->pid = _fork(shell);
	if (ast->leaf->pid == 0)
	{
		execute_nofork(shell, ast);
		if (shell->exit_code == -1)
			exit(1);
		else
			exit(shell->exit_code >> 8);
	}
}

void	execute_builtin(t_minishell_p shell, t_ast_p ast)
{
	if (ast->write_fd || ast->read_fd)
	{
		execute_wfork(shell, ast);
	}
	else
	{
		execute_nofork(shell, ast);
	}
}
