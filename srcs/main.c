/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:57:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/09 18:25:50 by cgajean          ###   ########.fr       */
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

static void	mainloop(t_shell_p shell, t_ast_p *ast)
{
	while (is_no_abort(shell))
	{
		prompt_input(shell);
		if (shell->input)
		{
			if (!*(shell->input))
				g_sigstatus = EXIT_SUCCESS;
			else if (tokenize_input(shell, &shell->exit_code))
			{
				if (parse_tokens(shell, ast))
				{
					execute_ast(shell, ast);
					destroy_ast(ast);
					shell->ast_root = NULL;
				}
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

int	main(int ac, char **av, char **env)
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
