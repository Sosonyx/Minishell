/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_heredoc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 16:30:25 by fox               #+#    #+#             */
/*   Updated: 2025/09/17 18:29:56 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*_expand_input_line(t_minishell_p shell, char *input_line)
{
	return (expand_old_cmd(shell, input_line).value);
}

static char	*_readline(t_minishell_p shell, t_redir_p redir)
{
	char	*line;

	line = readline(HEREDOC_SIGN);
	if (!line)
		print_hd_error(shell, redir->limiter);
	else
		shell->readlines++;
	return (line);
}

static ssize_t	_writeline(t_minishell_p shell, t_leaf_p leaf, t_redir_p redir, char *hd)
{
	char	*exp_hd;
	ssize_t	wbytes;

	wbytes = 0;
	if (hd && ft_strcmp(hd, redir->limiter))
	{
		exp_hd = _expand_input_line(shell, hd);
		if (exp_hd)
		{
			wbytes = write(leaf->hd_fd[1], exp_hd, ft_strlen(exp_hd));
			wbytes += write(leaf->hd_fd[1], "\n", 1);
			free(exp_hd);
		}
		if (hd)
			free(hd);
	}
	return (wbytes);
}

static void	_input_heredoc(t_minishell_p shell, t_leaf_p leaf, t_redir_p redir)
{
	pid_t	pid;

	if (pipe(leaf->hd_fd) == -1)
	{
		return (set_abort(shell, MEM_ERRMSG));
	}
	pid = fork();
	if (pid == 0)
	{
		close_secure(&leaf->hd_fd[0]);
		while (NO_ABORT)
		{
			if (!_writeline(shell, leaf, redir, _readline(shell, redir)))
				break ;
		}
		close_secure(&leaf->hd_fd[1]);
		exit(shell->abort);
	}
	else if (pid > 0)
	{
		waitpid(pid, &shell->exit_code, 0);
		if (shell->exit_code)
			set_abort(shell, PIP_ERRMSG);
	}
	else
		set_abort(shell, FORK_ERRMSG);
	close_secure(&leaf->hd_fd[1]);
}

void	input_heredoc(t_minishell_p shell, t_leaf_p leaf)
{
	t_redir_p	redir;

	redir = leaf->redir;
	while (NO_ABORT && redir)
	{
		if (redir->type & (R_IN | R_HDOC))
			close_secure(&leaf->hd_fd[0]);
		if (redir->type == R_HDOC)
			_input_heredoc(shell, leaf, redir);
		redir = redir->next;
	}
}
