/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:57:45 by ihadj             #+#    #+#             */
/*   Updated: 2025/08/27 17:50:21 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_status;
/*
	Gere le CTRL C, reaffiche un prompt clean
	A utiliser que dans le PARENT
	Dans l enfant : signal(SIGINT, SIG_DFL);
					signal(SIGQUIT, SIG_DFL);
*/
void sigint_handler(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

static void print_tab(t_arg a)
{
	int i;

	i = -1;
	while ((a.cmds)[++i])
	{
		printf("TOKEN_value = [%s] ------- TOKEN_type == [%d]\nDQuoted = [%d]\n", (a.cmds)[i]->val, (a.cmds)[i]->type, (a.cmds)[i]->was_double_quoted);
		printf("======================================================================\n");
	}
}

static void free_array(char **arr)
{
	int i;

	i = -1;
	while (arr[++i])
		free(arr[i]);
}

// int	main(void)
// {
// 	t_ast_p		ast;

// 	ast = calloc(1, sizeof(t_ast));
	
// 	ast.type = OP_AND;
// 	ast.cntl_op->left->cntl_op->left;
// 	ast.cntl_op->right->leaf;					//pas d'acces aux membres via intellisense

// 	ptr = ast.cntl_op->left->cntl_op->left;
	
// 	return (0);
// }

int main(int ac, char **av)
{
	extern char	**environ;
	char 		*line;
	t_arg		elem;

	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		line = readline("\001\033[48;5;57m\002minishell>\001\033[0m\002 ");
		if (!line)
		{
			printf("exit\n");
			break;
		}
		add_history(line);
		if (!stock_tokens(&elem, line))
		{
			g_status = 258;
			continue ;
		}
		if (!check_syntax(elem.cmds))
		{
			g_status = 258;
			// free_tokens(elem.cmds);
			free(line);
			continue ;
		}
		// parse();
		// expand();
		// exec();
		print_tab(elem);
		free(line);
	}
	rl_clear_history();
	return (0);
}
