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

static char	*_expand_input_line(t_shell_p shell, char *input_line)
{
	return (expand_command(shell, input_line).value);
}

static char	*_readline(t_shell_p shell, t_redir_p redir)
{
	char	*line;

	line = readline(HEREDOC_SIGN);
	if (!line)
		print_hd_error(shell, redir->limiter);
	else
		shell->readlines++;
	return (line);
}

static ssize_t	_writeline(t_shell_p shell, \
	t_leaf_p leaf, t_redir_p redir, char *hd)
{
	char	*expd_hd;
	ssize_t	wbytes;

	wbytes = 0;
	if (hd && ft_strcmp(hd, redir->limiter))
	{
		if (redir->expand_hd)
			expd_hd = hd;
		else
			expd_hd = _expand_input_line(shell, hd);
		if (expd_hd)
		{
			wbytes = write(leaf->hd_fd[1], expd_hd, ft_strlen(expd_hd));
			wbytes += write(leaf->hd_fd[1], "\n", 1);
			if (expd_hd != hd)
				free(expd_hd);
		}
		if (hd)
			free(hd);
	}
	return (wbytes);
}

static void	heredoc_signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		g_sigstatus = 130;
		close(0);
	}
}

static void	_input_heredoc(t_shell_p shell, \
	t_leaf_p leaf, t_redir_p redir)
{
	pid_t	pid;
	int		ret_code;

	ret_code = 0;
	pid = 0;
	if (_pipe(shell, leaf->hd_fd))
		return ;
	pid = _fork(shell);
	if (pid == 0)
	{
		close_secure(&leaf->hd_fd[0]);
		signal(SIGINT, heredoc_signal_handler);
		signal(SIGQUIT, SIG_IGN);
		while (is_no_abort(shell))
		{
			if (!_writeline(shell, leaf, redir, _readline(shell, redir)))
				break ;
		}
		close_secure(&leaf->hd_fd[1]);
		if (g_sigstatus == 130)
			ret_code = 130;
		else if (shell->abort == 1)
			ret_code = 1;
		(free_tokens_container(shell, shell->tokens), destroy_shell(shell));
		exit(ret_code);
	}
	else if (pid > 0)
	{
		signals_ign();
		waitpid(pid, &shell->exit_code, 0);
		signals_setter();
		// if (shell->exit_code)
		// 	set_abort(shell, PIP_ERRMSG);
	}
	close_secure(&leaf->hd_fd[0]);
	close_secure(&leaf->hd_fd[1]);
}

void	input_heredoc(t_shell_p shell, t_leaf_p leaf)
{
	t_redir_p	redir;

	redir = leaf->redir;
	while (is_no_abort(shell) && redir)
	{
		if (redir->type & (R_IN | R_HDOC))
			close_secure(&leaf->hd_fd[0]);
		if (redir->type == R_HDOC)
			_input_heredoc(shell, leaf, redir);
		redir = redir->next;
	}
}
