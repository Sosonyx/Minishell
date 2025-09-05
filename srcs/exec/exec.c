/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 12:15:52 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/05 15:20:29 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_status	exec_ast(t_ast_p ast)
{
	
}

// void	close_fd(int fd)
// {
// 	if (fd != -1)
// 		close(fd);
// }

// int	get_fd_in(char *file1)
// {
// 	int	fd_in;

// 	fd_in = open(file1, O_RDONLY);
// 	return (fd_in);
// }

// int	get_fd_out(char *file2)
// {
// 	int	fd_out;

// 	fd_out = open(file2, O_WRONLY | O_CREAT | O_TRUNC, 0644);
// 	return (fd_out);
// }

// void	execve_cmd(t_leaf *pipex, int i)
// {
// 	execve(pipex->cmd_paths[i], pipex->cmd_args[i], pipex->env);
// }

// void	dup2_and_closefd(int fd_in, int fd_out)
// {
// 	dup2(fd_in, STDIN_FILENO);
// 	dup2(fd_out, STDOUT_FILENO);
// 	close_fd(fd_in);
// 	close_fd(fd_out);
// }

// pid_t	first_redirection(t_leaf *cmds)
// {
//     int		fd_in;
//     pid_t	pid;

//     fd_in = get_fd_in(cmds->argv[0][0]);
//     if (pipe(cmds->pipefd) == -1)
//         return (perror("Pipe failed"), 2);
//     pid = fork();
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
