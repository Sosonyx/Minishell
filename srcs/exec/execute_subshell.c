/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/11 14:39:46 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	t_minishell_p	subshell;
	int				ret_code;

	subshell = shell_init(shell->ac, shell->av, shell->environ);
	if (subshell)
	{
		subshell->depth = shell->depth + 1;
		ret_code = execute_ast(subshell, ast->cntl_op->left);
		shell_destroy(subshell);
	}
	else
	{
		print_generic_error(MEM_ERRMSG);
		// restart immediat ou laisser finir ce qui peut etre fini ?
	}
	return (ret_code);
}
