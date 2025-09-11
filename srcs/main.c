/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:57:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/11 10:32:53 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_status;
/*
	Gere le CTRL C, reaffiche un prompt clean
	A utiliser que dans le PARENT
	Dans l enfant : signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
*/

static char	*prompt_input(char **input)
{
	*input = readline(PROMPT_MESSAGE);
	if (*input)
		add_history(*input);
	return (*input);
}


int	main(int ac, char **av, char **env)
{
	t_ast_p				ast = NULL;
	t_tok_container_p	tok_container = NULL;
	char				*input = NULL;
	t_minishell_p		shell;
	int					return_code;
	
	signals_setter();
	shell = shell_init(ac, av, environ);
	while (1)
	{
		if (prompt_input(&input))
		{
			if (tokenize_input(input, &tok_container, &g_status))		// return error non ? 
			{
				if (parse_tokens(&ast, tok_container))
				{
					ast->env = env;
					return_code = execute_ast(shell, ast);
					// exec
					// temporaire
					// destroy input + destroy ast
					// execve(ast->leaf->cmds[0], ast->leaf->cmds, env);
					free(ast);
				}
				else
				{
					// ast error -> close ou message d'erreur et nouveau prompt ?
				}
			}
		}
		else
		{
			if (!input)
			{
				// printf("exit\n");
				break ;
			}	
					// prompt error -> close ou message d'erreur et nouveau prompt ?
		}
	}
	rl_clear_history();
	return (return_code);
}

























//////////////////////////////////////////////////////////////////////////////////////////

// main.c initial

// int g_status;
// /*
// 	Gere le CTRL C, reaffiche un prompt clean
// 	A utiliser que dans le PARENT
// 	Dans l enfant : signal(SIGINT, SIG_DFL);
// 					signal(SIGQUIT, SIG_DFL);
// */
// void sigint_handler(int sig)
// {
// 	(void)sig;
// 	write(1, "\n", 1);
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// static void print_tab(t_tok_container a)
// {
// 	int i;

// 	i = -1;
// 	while ((a.cmds)[++i])
// 	{
// 		printf("TOKEN_value = [%s] ------- TOKEN_type == [%d]\nDQuoted = [%d]\n", (a.cmds)[i]->val, (a.cmds)[i]->type, (a.cmds)[i]->was_double_quoted);
// 		printf("======================================================================\n");
// 	}
// }

// static void free_array(char **arr)
// {
// 	int i;

// 	i = -1;
// 	while (arr[++i])
// 		free(arr[i]);
// }

// int main(int ac, char **av)
// {
// 	extern char	**environ;
// 	char 		*line;
// 	t_tok_container		elem;

// 	signal(SIGINT, sigint_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	while (1)
// 	{
// 		line = readline("\001\033[48;5;57m\002minishell>\001\033[0m\002 ");
// 		if (!line)
// 		{
// 			printf("exit\n");
// 			break;
// 		}
// 		add_history(line);
// 		if (!stock_tokens(&elem, line))
// 		{
// 			g_status = 258;
// 			continue ;
// 		}
// 		if (!check_syntax(elem.cmds))
// 		{
// 			g_status = 258;
// 			// free_tokens(elem.cmds);
// 			free(line);
// 			continue ;
// 		}
// 		// parse();
// 		// expand();
// 		// exec();
// 		print_tab(elem);
// 		free(line);
// 	}
// 	rl_clear_history();
// 	return (0);
// }
