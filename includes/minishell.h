/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/20 17:18:26 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# ifndef _GNU_SOURCE
#  define _GNU_SOURCE
# endif

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>
# include <dirent.h>

# include "minishell_typedefs.h"
# include "minishell_structures_enums.h"
# include "minishell_parsing.h"
# include "minishell_error_and_signal_manager.h"
# include "minishell_exec.h"
# include "wildcards.h"

# include "libft.h"

# define PROMPT_MESSAGE "\001\033[48;5;80m\002minishell>\001\033[0m\002 "
# define HEREDOC_SIGN	">"

# define LOAD_FAIL_MSG "Minishell failed at loading!\n"

# define OPEN_PERM 0644

extern int	g_sigstatus;

/*****************************************************************************/
/*			Minishell														 */
/*****************************************************************************/

t_shell_p	shell_init(int ac, char **av, char **envp);
void		destroy_shell(t_shell_p shell);
void		shell_kill(t_shell_p shell);
void		shell_reset(t_shell_p shell);

/*****************************************************************************/
/*			Wrappers														 */
/*****************************************************************************/

void		*_malloc(t_shell_p shell, size_t size);
void		*_calloc(t_shell_p shell, size_t nmemb, size_t size);
void		*_realloc(t_shell_p shell, \
	void *ptr, size_t old_size, size_t new_size);

char		*_strdup(t_shell_p shell, const char *s);
char		*_strjoin(t_shell_p shell, char const *s1, char const *s2);
char		**_split(t_shell_p shell, const char *s, const char c);
char		**_split_clone(t_shell_p shell, char **strs);

int			_pipe(t_shell_p shell, int *pipedes);
int			_dup(t_shell_p shell, int fd);
int			_dup2(t_shell_p shell, int fd, int fd2);
pid_t		_fork(t_shell_p shell);

char		*_getcwd(t_shell_p shell, char **buf);

#endif
