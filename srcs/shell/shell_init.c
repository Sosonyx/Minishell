/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_init.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:51:58 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:21:23 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_minishell_p	shell_init(int ac, char **av, char **envp)
{
	t_minishell_p	new_shell;
	
	new_shell = ft_calloc(1, sizeof(struct s_minishell));
	if (!new_shell)
	{
		//	ajouter argv[1];
		print_generic_error(NULL, MEM_ERRMSG);
		exit(EXIT_FAILURE);
	}
	else
	{
		new_shell->ac = ac;
		new_shell->av = av;
		new_shell->environ = dup_env(envp);
		// new_shell->readlines++;
	}
	return (new_shell);
}
