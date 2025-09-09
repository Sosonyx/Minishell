/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/09 11:25:10 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 14:10:37 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_builtin(t_ast_p ast)
{
	char	*cmd;

	if (!ast->leaf->cmds || !ast->leaf->cmds[0]) // si NULL ? jsplus si on l a testee avant
		return (false);
	cmd = ast->leaf->cmds[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (true); //on peut exec ici mais vaut mieux decouper en deux blocs distincts selon moi
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

int	execute_builtin(t_minishell_p shell, t_ast_p ast)
{
	char	*cmd;

	cmd = ast->leaf->cmds[0];
	if (ft_strcmp(cmd, "echo") == 0)
		return (ft_echo(ast->leaf->cmds));
	if (ft_strcmp(cmd, "cd") == 0)
		return (ft_cd(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "pwd") == 0)
		return (ft_pwd());
	if (ft_strcmp(cmd, "export") == 0)
		return (ft_export(shell, &ast->leaf->cmds[1])); // pas prendre la premiere cmd
	if (ft_strcmp(cmd, "unset") == 0)
		return (ft_unset(shell, ast->leaf->cmds));
	if (ft_strcmp(cmd, "env") == 0)
		return (ft_env(shell->environ));
	// if (ft_strcmp(cmd, "exit") == 0) // exit a revoir
		// return (ft_exit(ast->leaf->cmds, shell));
	else
		return (EXIT_FAILURE);
}
