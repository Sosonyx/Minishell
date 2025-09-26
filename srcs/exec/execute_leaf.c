/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 15:07:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/26 20:12:58 by fox              ###   ########.fr       */
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


static int	isfile(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISREG(file_stat.st_mode))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static int	isdir(char *path)
{
	struct stat	file_stat;

	if (stat(path, &file_stat) == 0)
	{
		if (S_ISDIR(file_stat.st_mode))
			return (1);
		else
			return (0);
	}
	else
		return (0);
}

static int	islocalfile(char *filepath)
{
	if (ft_strncmp(filepath, "./", 2))
		return (0);
	else
		return (1);
}

static void	_execve(t_minishell_p shell, t_ast_p ast)
{
	int	errnum;

	errnum = 0;
	
	if (isdir(ast->leaf->full_path))
	{
		if (ft_strncmp(ast->leaf->full_path, "./", 2))
			errnum = ENOENT;
		else
			errnum = EISDIR;
	}
	if (errnum)
	{
		print_cmd_error(shell, *ast->leaf->cmds, errnum);
		exit(convert_errno(errnum));
	}
	else
	{
		execve(ast->leaf->full_path, ast->leaf->cmds, shell->environ);
		print_cmd_error(shell, *ast->leaf->cmds, errno);
		exit(convert_errno(errno));
	}
}

static void	_execute_command(t_minishell_p shell, t_ast_p ast)
{
	int		errnum;
	int		access_value;

	if (ast->leaf->fds[0] == -1 || ast->leaf->fds[1] == -1)
		exit(convert_errno(ENOENT));
	redirect_leaf(shell, ast);
	close_fds(ast, CHILD);
	if (ast->leaf->abort == true)
	{
		exit(EXIT_FAILURE);
	}
	else if (!*ast->leaf->cmds)
	{
		exit(EXIT_SUCCESS);
	}
	else
	{
		_execve(shell, ast);

		// le code actuel est une aide à la réflexion non aboutie
		
		// il faut distinguer les chemins locaux et absolus.

		// Nous avons actuellement deux problèmes : 

		//	1) Des commandes comme "minishell" fonctionnent, alors qu'elles ne devraient pas
		//	(seul ./minishell devrait être accepté)
		
		// 	2) stat() et access() parviennent à trouver n'importe quel fichier local, en plus du PATH
		// 	par conséquent ils ne peuvent pas, seuls, servir à tester une commande

		// il faut en amont (à la construction de la commande) savoir si c'est un chemin direct (./minishell, /usr/bin/ls) 
		// ou non, et effectuer nous-mêmes les recherches au(x) bon(s) endroit(s) pour décider d'execve ou non
	}
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
