/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_kill.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 16:54:50 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/09 10:04:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	shell_kill(t_minishell_p shell, t_ast_p ast, char *errmsg)
{
	print_generic_error("Fatal error. Exit now...\n");
	if (shell)
		;	//	destroy_shell(shell);
	if (ast)
		;	//	destroy_ast(ast);
	exit(EXIT_FAILURE);
}
