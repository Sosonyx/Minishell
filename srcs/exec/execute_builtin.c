/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:10 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/21 15:14:46 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command(t_shell_p shell, t_ast_p ast)
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
		return (ft_exit(ast, shell, ast->leaf->cmds));
	else
		return (EXIT_FAILURE);
}

void	_execute(t_shell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		if (redirect_leaf(shell, ast) == -1)
			shell->exit_code = -1;
		else
			shell->exit_code = execute_command(shell, ast);
		close_fds(shell, ast, CHILD);
	}	
}

void	execute_nofork(t_shell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		save_std_fileno(shell);
		_execute(shell, ast);
		restore_std_fileno(shell, ast);
	}
}

void	execute_wfork(t_shell_p shell, t_ast_p ast)
{
	int	retcode;

	ast->leaf->pid = _fork(shell);
	if (ast->leaf->pid == 0)
	{
		_execute(shell, ast);
		if (shell->exit_code == -1)
		{
			destroy_shell(shell);
			exit(EXIT_FAILURE);
		}
		else
		{
			retcode = shell->exit_code >> 8;
			destroy_shell(shell);
			exit(retcode);
		}
	}
	else if (ast->leaf->pid > 0)
	{
		close_fds(shell, ast, PARENT);
	}
}

void	execute_builtin(t_shell_p shell, t_ast_p ast)
{
	if (is_no_abort(shell))
	{
		if (ast->write_fd || ast->read_fd)
			execute_wfork(shell, ast);
		else
			execute_nofork(shell, ast);
	}
}
