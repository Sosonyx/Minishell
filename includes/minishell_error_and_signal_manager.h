/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_and_signal_manager.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:37:01 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 18:17:00 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef MINISHELL_ERROR_AND_SIGNAL_MANAGER_H
# define MINISHELL_ERROR_AND_SIGNAL_MANAGER_H

# define FILE_ERRMSG	"No such file or directory"
# define CMD_ERRMSG		"command not found"
# define MEM_ERRMSG		"Memory error. Try again or restart Minishell.\n"
# define PIP_ERRMSG		"Pipe error. Try again or restart Minishell.\n"
# define FORK_ERRMSG	"Fork error. Try again or restart Minishell.\n"
# define AST_ERRMSG		"Execution failed. Try again or restart Minishell.\n"

# define LEN_INTMAX		12

# ifdef NEWLINE
#  undef NEWLINE
#   define NEWLINE "\n"
# endif

# define SELF "Minishell"
# define COLUMN ": "


/********************************************************************************/
/*			Errors																*/
/********************************************************************************/

void	speak(t_minishell_p shell, int fd, char *announce, char *separator);
void	print_file_error(t_minishell_p shell, char *filename, int err_num);
void	print_cmd_error(t_minishell_p shell, char *cmd_name, int err_num);
void	print_generic_error(t_minishell_p shell, char *errmsg);
void	print_hd_error(t_minishell_p shell, char *limiter);

/********************************************************************************/
/*			Signals																*/
/********************************************************************************/

void	sigint_handler(int sig);
void	signals_setter(void);

#endif
