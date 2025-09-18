/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:10 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 14:11:32 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_leaf_p leaf)
{
	char	*cmd;

	if (!leaf->cmds || !leaf->cmds[0])
		return (false);
	cmd = leaf->name;
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

static int	 _execute_builtin(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;

	cmd = ast->leaf->name;
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(ast->leaf->cmds));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd(ast->leaf->cmds));
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell, &ast->leaf->cmds[1]));
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(shell->environ, ast->leaf->cmds));
	if (ft_strcmp(cmd, "exit") == 0) // exit doit appeler CLEANEXIT
		return (ft_exit(ast->leaf->cmds, shell->last_status));
	else
		return (EXIT_FAILURE);
}

void	execute_builtin(t_minishell_p shell, t_ast_p ast)
{
	save_std_fileno(shell);
	redirect_leaf(shell, ast);
	shell->last_status = _execute_builtin(shell, ast);
	restore_std_fileno(shell, ast);
}
