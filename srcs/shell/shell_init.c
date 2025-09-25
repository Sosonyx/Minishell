/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:58 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/25 10:09:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_minishell_help(int ac, char **av)
{
	if (ac == 2 && !ft_strcmp(av[1], "--help"))
		minishell_help();		
}

t_minishell_p	_shell_init(int ac, char **av, char **envp)
{
	t_minishell_p	new_shell;
	
	new_shell = ft_calloc(1, sizeof(struct s_minishell));
	if (!new_shell)
	{
		print_generic_error(NULL, MEM_ERRMSG);
		exit(EXIT_FAILURE);
	}
	else
	{
		new_shell->ac = ac;
		new_shell->av = av;
		new_shell->environ = dup_env(envp); // if ENV NULL recreer un petit env
		if (ft_strncmp(*av, "./", 2) == 0)
			new_shell->name = *av + 2;
		else
			new_shell->name = *av;
	}
	return (new_shell);
}

t_minishell_p	shell_init(int ac, char **av, char **envp)
{
	signals_setter();
	_minishell_help(ac, av);
	return (_shell_init(ac, av, envp));
}
