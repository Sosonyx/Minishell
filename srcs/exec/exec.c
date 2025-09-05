/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:15:52 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/05 17:52:00 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define SELF "Minishell: "

static void self_announce(int target_fd)
{
	write(target_fd, SELF, ft_strlen(SELF));
}

static void self_speak(int target_fd, char *msg, char *target)
{
	self_announce(target_fd);
	write(target_fd, target, ft_strlen(target));
	write(1, ": ", 2);
	write(target_fd, msg, ft_strlen(SELF));
	write(1, "\n", 1);
}

void close_fd(int fd)
{
	if (fd != -1)
		close(fd);
}

int get_fd_in(t_ast_p ast)
{
	char *target;
	int fd_in;
	int prev = 0;

	while (ast->leaf->redir)
	{
		if (ast->leaf->redir->type == T_REDIR_IN)
			target = ast->leaf->redir->target;
		fd_in = open(target, O_RDONLY);
		if (fd_in == -1)
		{
			self_speak(2, "No such file or directory", target);
			close(prev);
			break;
		}
		else
		{
			close(prev);
			prev = fd_in;
		}
		ast->leaf->redir = ast->leaf->redir->next;
	}
	return (fd_in);
}

int get_fd_out(t_ast_p ast)
{
	char *target;
	int fd_out;
	int prev = 0;

	while (ast->leaf->redir)
	{
		if (ast->leaf->redir->type == T_REDIR_OUT || ast->leaf->redir->type == T_APPEND)
			target = ast->leaf->redir->target;
		if (fd_out == T_REDIR_OUT)
		{
			fd_out = open(target, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (fd_out == -1)
			{
				self_speak(2, "No such file or directory", target);
				close(prev);
				break;
			}
			else
			{
				close(prev);
				prev = fd_out;
			}
		}
		else
		{
			fd_out = open(target, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (fd_out == -1)
			{
				self_speak(2, "No such file or directory", target);
				close(prev);
				break;
			}
			else
			{
				close(prev);
				prev = fd_out;
			}
		}
		ast->leaf->redir = ast->leaf->redir->next;
		prev = fd_out;
	}

	return (fd_out);
}

void dup2_and_closefd(int fd_in, int fd_out)
{
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close_fd(fd_in);
	close_fd(fd_out);
}

// void	heredoc_gestion(t_ast_p ast)
// {
// 	char	*line;
// 	int		len;

// 	ft_putstr("> ");
// 	line = get_next_line(0);
// 	while (line)
// 	{
// 		len = ft_strlen(line);
// 		if (len > 0 && line[len - 1] == '\n')
// 			line[len - 1] = '\0';
// 		if (!ft_strcmp(line, ast->leaf->redir->limiter))
// 		{
// 			free(line);
// 			return ;
// 		}
// 		ft_putstr("> ");
// 		ft_putstr_fd(line, p->hdpipe[1]);
// 		ft_putstr_fd("\n", p->hdpipe[1]);
// 		free(line);
// 		line = get_next_line(0);
// 	}
// }

// int	heredoc_redirection(t_ast_p ast)
// {
// 	if (pipe(pipex->hdpipe) == -1)
// 		return (perror("Pipe failed"), 2);
// 	heredoc_gestion(pipex);
// 	close(pipex->hdpipe[1]);
// 	return (pipex->hdpipe[0]);
// }

void exec_cntl_op(t_ast_p ast, t_ast_branch branch);
void exec_pipe_op(t_ast_p ast, t_ast_branch branch);
void exec_subshell(t_ast_p ast, t_ast_branch branch);

t_error_status exec_leaf(t_ast_p ast)
{
	int		fd_in;
	int		fd_out;
	pid_t	pid;
	int		status;
	int		exit_code;

	fd_in = get_fd_in(ast);
	if (fd_in == -1)
		return (RETURN_FAIL);
	fd_out = get_fd_out(ast);
	// if (is_built_in(ast->leaf->cmds[0]))
		// exec_built_in(ast->leaf->cmds[0]);
	pid = fork();
	if (pid == 0)
	{
		dup2_and_closefd(fd_in, fd_out);
		execve(ast->leaf->cmds[0], ast->leaf->cmds, ast->env);
		exit(errno);
	}
	return (RETURN_OK);
}

static int	get_exit_code(void)
{
	int	status;
	int	exit_code;

	status = 0;
	exit_code = 0;
	if (waitpid(-1, &status, 0) > 0)
	{
		if (WIFEXITED(status))
			exit_code = WEXITSTATUS(status);
		// sigterm ??
	}
	return exit_code;
}

void	exec_branch(t_ast_p ast, t_ast_branch branch, void (*f)(t_ast_p, t_ast_branch))
{
	int	exit_code;

	exit_code = -1;
	if (branch & LEFT_BRANCH)
		f(ast->cntl_op->left, LEFT_BRANCH);
	exit_code = get_exit_code();
	if ((ast->type == OP_OR && exit_code != 0) || (ast->type == OP_AND && exit_code == 0) || (ast->type == OP_PIPE))
	{
		f(ast->cntl_op->right, RIGHT_BRANCH);
	}
}

t_error_status	exec_ast(t_ast_p ast, t_ast_branch branch)
{
	void (*f)(t_ast_p, t_ast_branch) = NULL;
	int way = 0;

	if (!ast)
		return RETURN_FAIL;

	if (ast->leaf)
	{
		if (branch == RIGHT_BRANCH || branch == LEFT_BRANCH)
			return (exec_leaf(ast));
		return (RETURN_OK);
	}
	else
	{
		if (ast->type == OP_AND || ast->type == OP_OR)
		{
			way = LEFT_BRANCH | RIGHT_BRANCH;
			f = exec_cntl_op;
		}
		else if (ast->type == OP_PIPE)
		{
			way = LEFT_BRANCH | RIGHT_BRANCH;
			f = exec_pipe_op;
		}
		else if (ast->type == OP_SUBSHELL)
		{
			way = LEFT_BRANCH;
			f = exec_subshell;
		}
		if (f)
			exec_branch(ast, way, f);
	}
	return (RETURN_OK);
}

void exec_cntl_op(t_ast_p ast, t_ast_branch branch)
{
	exec_ast(ast, branch);
}

void exec_pipe_op(t_ast_p ast, t_ast_branch branch)
{
	exec_ast(ast, branch);
}

void exec_subshell(t_ast_p ast, t_ast_branch branch)
{
	exec_ast(ast, branch);
}



// pid_t	first_redirection(t_leaf *cmds)
// {
//     int		fd_in;
//     pid_t	pid;

//     fd_in = get_fd_in(cmds->argv[0][0]);
//     if (pipe(cmds->pipefd) == -1)
//         return (perror("Pipe failed"), 2);
//     pid = ();
//     if (pid == 0)
//     {
//         if (fd_in == -1)
//             clean_ex_chd(cmds, exit_code(), 1);
//         dup2_and_closefd(fd_in, cmds->pipefd[1]);
//         close_fd(cmds->pipefd[0]);
//         execve_cmd(cmds, cmds->argv[0], cmds);
//         perror("command not found");
//         clean_ex_chd(cmds, exit_code(), 0);
//     }
//     close_fd(fd_in);
//     close_fd(cmds->pipefd[1]);
//     return (pid);
// }

// int	multiple_redirections(t_leaf *pipex)
// {
// 	int		i;
// 	pid_t	pid;
// 	int		curr_pipefd[2];

// 	i = 0;
// 	if (pipex->here_doc == 1)
// 		i = 1;
// 	curr_pipefd[0] = -1;
// 	curr_pipefd[1] = -1;
// 	while (++i < pipex->ac - 4)
// 	{
// 		pipe(curr_pipefd);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			dup2_and_closefd(pipex->pipefd[0], curr_pipefd[1]);
// 			close_fd(curr_pipefd[0]);
// 			execve_cmd(pipex, i);
// 			(perror("command not found"), clean_ex_chd(pipex, exit_code(), 1));
// 		}
// 		close_fd(pipex->pipefd[0]);
// 		close_fd(curr_pipefd[1]);
// 		pipex->pipefd[0] = curr_pipefd[0];
// 	}
// 	return (pipex->pipefd[0]);
// }

// pid_t	last_redirection(int pipefd, t_leaf *pipex)
// {
//     int		fd_out;
//     pid_t	pid;
//     int		last;

//     last = pipex->ac - 1;
//     fd_out = get_fd_out(pipex->argv[last][0]);
//     pid = fork();
//     if (pid == 0)
//     {
//         if (access(pipex->argv[last][0], W_OK))
//         {
//             perror("access");
//             clean_ex_chd(pipex, 1, 1);
//         }
//         dup2_and_closefd(pipefd, fd_out);
//         execve_cmd(pipex, pipex->argv[last], pipex);
//         perror("command not found");
//         clean_ex_chd(pipex, exit_code(), 0);
//     }
//     close_fd(pipefd);
//     close_fd(fd_out);
//     return (pid);
// }

// int	run_pipex(t_leaf *pipex)
// {
//     pid_t	last_pid;
//     int		status;
//     int		exit_code;

//     status = 0;
//     exit_code = 0;
//     if (first_redirection(pipex) == -1)
//         return (free_pipex(pipex), 1);
//     last_pid = last_redirection(pipex->pipefd[0], pipex);
//     if (last_pid == -1)
//         return (free_pipex(pipex), 1);
//     if (waitpid(last_pid, &status, 0) && WIFEXITED(status))
//         exit_code = WEXITSTATUS(status);
//     wait_all(pipex);
//     free_pipex(pipex);
//     return (exit_code);
// }
