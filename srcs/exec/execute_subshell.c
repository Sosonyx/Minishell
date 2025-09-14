/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_subshell.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/11 14:21:39 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/12 19:50:42 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int execute_subshell(t_minishell_p shell, t_ast_p ast)
{
	int				ret_code;
	pid_t			pid;

	pid = fork();
	if (pid == 0)
	{
		ast->cntl_op->left->read_fd = ast->read_fd;
		ast->cntl_op->left->write_fd = ast->write_fd;
			
		ret_code = execute_ast(shell, ast->cntl_op->left);
		exit(ret_code);
	}
	else if (pid > 0)
	{
		close_fds(ast, 0);
		waitpid(pid, &ret_code, 0);
	}
	else
	{
		print_generic_error(FORK_ERRMSG);
	}
	return (ret_code);
}

