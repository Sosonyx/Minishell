/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/27 14:27:06 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	convert_errno(int err)
{
	if (err == ENOENT)
		return (127);
	if (err == EACCES || err == EISDIR)
		return (126);
	return (1);
}

static int	check_path(char *path)
{
	struct stat	file_stats;

	if (!path)
		return (ENOENT);
	if (ft_strchr(path, '/'))
	{
		if (stat(path, &file_stats) != 0)
			return (ENOENT);
		if (S_ISDIR(file_stats.st_mode))
			return (EISDIR);
		if (access(path, X_OK) != 0)
			return (EACCES);
		return (0);
	}
	return (ENOENT);
}

// static void	_execve(t_minishell_p shell, t_ast_p ast)
// {
// 	int	errnum;

// 	errnum = check_path(ast->leaf->full_path);
// 	if (errnum == EISDIR || errnum == EACCES)
// 	{
// 		print_cmd_error(shell, *ast->leaf->cmds, errnum);
// 		exit(convert_errno(errnum));
// 	}
// 	execve(ast->leaf->full_path, ast->leaf->cmds, shell->environ);
// 	print_cmd_error(shell, *ast->leaf->cmds, errno);
// 	exit(convert_errno(errno));
// }

static void	_execve(t_minishell_p shell, t_ast_p ast)
{
	int	errnum;

	errnum = check_path(ast->leaf->full_path);
	if (errnum) // on met a jour errnum, si 0 pas d erreurs donc on exec
	{
		print_cmd_error(shell, *ast->leaf->cmds, errnum);
		exit(convert_errno(errnum)); // clean exit surement ici
	}
	execve(ast->leaf->full_path, ast->leaf->cmds, shell->environ);
	print_cmd_error(shell, *ast->leaf->cmds, errno);
	exit(convert_errno(errno));
}

static void	_execute_command(t_minishell_p shell, t_ast_p ast)
{
/* 	if (ast->leaf->fds[0] == -1 || ast->leaf->fds[1] == -1)
		exit(convert_errno(ENOENT)); */		// à ce stade ça ne devrait jamais arriver puisqu'on n'a pas encore touché aux leaf->fds
	redirect_leaf(shell, ast);
	close_fds(ast, CHILD);
	if (ast->leaf->abort == true)
		exit(EXIT_FAILURE);
	if (!*ast->leaf->cmds)
		exit(EXIT_SUCCESS);
	_execve(shell, ast);
}

static void	execute_command(t_minishell_p shell, t_ast_p ast)
{
	pid_t	*pid;

	ast->leaf->pid = fork();
	if (ast->leaf->pid == -1)
	{
		;
	}
	if (ast->leaf->pid == 0)
	{
		_execute_command(shell, ast);
	}
	else
	{
		close_fds(ast, PARENT);
	}
}

int	execute_leaf(t_minishell_p shell, t_ast_p ast)
{
	variable_expand(shell, ast);
	if (!ast->leaf->configured)
		preconfig_leaf(shell, ast->leaf);
	wildcard_expand(&ast->leaf->cmds);
	if (is_builtin(ast->leaf))
	{
		execute_builtin(shell, ast);	
		return (shell->last_status);
	}
	execute_command(shell, ast);
	return (0);
}







// static void	_execve(t_minishell_p shell, t_ast_p ast)
// {
// 	int	errnum;

// 	errnum = 0;
	
// 	if (isdir(ast->leaf->full_path))
// 	{
// 		if (ft_strncmp(ast->leaf->full_path, "./", 2))
// 			errnum = ENOENT;
// 		else
// 			errnum = EISDIR;
// 	}
// 	if (errnum)
// 	{
// 		print_cmd_error(shell, *ast->leaf->cmds, errnum);
// 		exit(convert_errno(errnum));
// 	}
// 	else
// 	{
// 		execve(ast->leaf->full_path, ast->leaf->cmds, shell->environ);
// 		print_cmd_error(shell, *ast->leaf->cmds, errno);
// 		exit(convert_errno(errno));
// 	}
// }
