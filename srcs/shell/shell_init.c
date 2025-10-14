/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:58 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 15:27:56 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	realloc_env(int i, char ***envp, char *value, char *name)
{
	char	**new_env;
	char	*new_var;

	new_env = malloc(sizeof(char *) * (i + 2));
	if (!new_env)
		return ;
	i = 0;
	while ((*envp)[i])
	{
		new_env[i] = (*envp)[i];
		i++;
	}
	new_var = ft_strjoin(name, "=");
	if (!new_var)
	{
		free(new_env);
		return ;
	}
	new_env[i] = ft_strjoin(new_var, value);
	free(new_var);
	new_env[i + 1] = NULL;
	free(*envp);
	*envp = new_env;
}

static void	change_value(char ***envp, char *name, char *value)
{
	int		i;
	size_t	name_len;
	char	*new_var;

	name_len = ft_strlen(name);
	i = 0;
	while ((*envp)[i])
	{
		if (!ft_strncmp((*envp)[i], name, name_len)
			&& (*envp)[i][name_len] == '=')
		{
			new_var = ft_strjoin(name, "=");
			if (!new_var)
				return ;
			free((*envp)[i]);
			(*envp)[i] = ft_strjoin(new_var, value);
			free(new_var);
			return ;
		}
		i++;
	}
	realloc_env(i, envp, value, name);
}

static void	set_shell_lvl(t_shell_p shell)
{
	char	*lvl_str;
	int		lvl;

	lvl_str = get_env_value(shell, "SHLVL");
	if (lvl_str)
	{
		lvl = ft_atoi(lvl_str);
		free(lvl_str);
	}
	else
		lvl = 1;
	lvl_str = ft_itoa(lvl);
	if (!lvl_str)
	{
		print_generic_error(NULL, MEM_ERRMSG);
		shell->exit_code = ERRVAL1;
	}
	else
	{
		change_value(&shell->environ, "SHLVL", lvl_str);
		free(lvl_str);
	}
}

t_shell_p	_shell_init(int ac, char **av, char **envp)
{
	t_shell_p	new_shell;

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
		new_shell->environ = dup_env(new_shell, envp);
		if (!new_shell->environ)
		{
			print_generic_error(NULL, MEM_ERRMSG);
			(free(new_shell), exit(EXIT_FAILURE));
		}
		set_shell_lvl(new_shell);
		if (ft_strncmp(*av, "./", 2) == 0)
			new_shell->name = *av + 2;
		else
			new_shell->name = *av;
	}
	return (new_shell);
}

t_shell_p	shell_init(int ac, char **av, char **envp)
{
	signals_setter();
	return (_shell_init(ac, av, envp));
}
