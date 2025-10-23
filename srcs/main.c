/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:57:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/23 13:06:31 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sigstatus = 0;

static void	prompt_input(t_shell_p shell)
{
	if (shell->input)
		free(shell->input);
	shell->input = readline(PROMPT_MESSAGE);
	if (shell->input && *shell->input)
	{
		add_history(shell->input);
		shell->readlines++;
	}
}

static void	catch_sig(t_shell_p shell)
{
	if (g_sigstatus)
	{
		shell->exit_code = 128 + g_sigstatus;
		g_sigstatus = 0;
	}
}

static void	mainloop(t_shell_p shell, t_ast_p *ast)
{
	while (1)
	{
		prompt_input(shell);
		catch_sig(shell);
		if (shell->input)
		{
			if (!*(shell->input))
				shell->exit_code = EXIT_SUCCESS;
			else if (tokenize_input(shell))
			{
				parse_tokens(shell, ast);
				(execute_ast(shell, ast), destroy_ast(ast));
				free_tokens_container(shell);
				shell_reset(shell);
			}
			else
				shell->exit_code = ERRVAL2;
		}
		else
		{
			ft_putstr_fd("exit\n", STDOUT_FILENO);
			break ;
		}
	}
}

int	main(int ac, char **av)
{
	t_ast_p				ast;
	t_shell_p			shell;
	int					return_status;

	ast = NULL;
	shell = shell_init(ac, av, environ);
	mainloop(shell, &ast);
	return_status = shell->exit_code;
	destroy_shell(shell);
	return (extract_return_code(return_status));
}
