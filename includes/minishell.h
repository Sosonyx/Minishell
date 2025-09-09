/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/09 11:05:39 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>

# include "minishell_typedefs.h"
# include "minishell_structures_enums.h"
# include "minishell_parsing.h"
# include "minishell_error_and_signal_manager.h"
# include "minishell_messager.h"
# include "minishell_exec.h"

# include "libft.h"

# define PROMPT_MESSAGE "\001\033[48;5;57m\002minishell>\001\033[0m\002 "
# define SHELL_TABLES_SIZE 32
# define LOAD_FAIL_MSG "Minishell failed at loading!\n"

/********************************************************************************/
/*			Minishell															*/
/********************************************************************************/

t_minishell_p	shell_init(int ac, char **av, char **envp);

void			shell_destroy(t_minishell_p shell);

void			shell_kill(t_minishell_p shell, t_ast_p ast, char *errmsg);

void			shell_restart(t_minishell_p shell, t_ast_p ast);

#endif
