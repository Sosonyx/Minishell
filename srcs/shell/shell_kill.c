/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_kill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:54:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:18:19 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_kill(t_minishell_p shell, t_ast_p ast, char *errmsg)
{
	print_generic_error(shell, "Fatal error. Exit now...\n");
	if (shell)
		;	//	destroy_shell(shell);
	if (ast)
		;	//	destroy_ast(ast);
	exit(EXIT_FAILURE);
}
