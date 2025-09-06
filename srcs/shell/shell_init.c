/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:58 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 18:42:17 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	pid_table_init(t_minishell_p shell)
{
	shell->exec_var.pid_table = ft_calloc(SHELL_TABLES_SIZE, sizeof(int *));
	if (!shell->exec_var.pid_table)
	{
		shell_kill(shell, NULL, LOAD_FAIL_MSG);
	}
	else
		shell->exec_var.tables_size = SHELL_TABLES_SIZE;
	return ;
}

static void	status_table_init(t_minishell_p shell)
{
	shell->exec_var.status_table = ft_calloc(SHELL_TABLES_SIZE, sizeof(int *));
	if (!shell->exec_var.status_table)
	{
		shell_kill(shell, NULL, LOAD_FAIL_MSG);
	}
	else
		shell->exec_var.tables_size = SHELL_TABLES_SIZE;
	return ;
}

t_minishell_p	shell_init(int ac, char **av, char **envp)
{
	t_minishell_p	new_shell;
	
	new_shell = ft_calloc(1, sizeof(struct s_minishell));
	if (!new_shell)
	{
		shell_kill(new_shell, NULL, LOAD_FAIL_MSG);
	}
	else
	{
		new_shell->argc = ac;
		new_shell->argv = av;
		new_shell->environ = envp;
		pid_table_init(new_shell);
		status_table_init(new_shell);
		//error_code_table ?
	}
	return (new_shell);
}
