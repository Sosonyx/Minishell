/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_and_signal_manager.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:37:01 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/01 15:35:24 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef MINISHELL_ERROR_AND_SIGNAL_MANAGER_H
# define MINISHELL_ERROR_AND_SIGNAL_MANAGER_H

# define FILE_ERRMSG		"No such file or directory"
# define CMD_ERRMSG			"command not found"
# define MEM_ERRMSG			"Memory error. Try again or restart Minishell."
# define PIP_ERRMSG			"Pipe error. Try again or restart Minishell."
# define FORK_ERRMSG		"Fork error. Try again or restart Minishell."
# define AST_ERRMSG			"Execution failed. Try again or restart Minishell."
# define ARG_EXCESS_ERRMSG	"too many arguments"
# define ARG_NON_NUM_ERRMSG	"numeric argument required"
# define INVALID_ID_ERRMSG	"not a valid identifier"
# define DIRECTORY_ERRMSG   "Is a directory"
# define PERMISSION_ERRMSG  "Permission denied"
# define EOF_ERRMSG			"minishell: unexpected EOF while looking for matching quote\n"

# define LEN_INTMAX		12

# ifdef NEWLINE
#  undef NEWLINE
#  define NEWLINE "\n"
# endif

# define SELF "Minishell"
# define COLUMN ": "

# define ERRVAL1 256
# define ERRVAL2 512

/********************************************************************************/
/*			Errors																*/
/********************************************************************************/

void	speak(t_minishell_p shell, int fd, char *announce, char *separator);
void	print_file_error(t_minishell_p shell, char *filename, int err_num);
void	print_cmd_error(t_minishell_p shell, char *cmd_name, int err_num);
void	print_cmd_error2(t_minishell_p shell, char *cmd_name, char *errmsg);
void	print_generic_error(t_minishell_p shell, char *errmsg);
void	print_hd_error(t_minishell_p shell, char *limiter);
void	set_abort(t_minishell_p shell, char *errmsg);


/********************************************************************************/
/*			Signals																*/
/********************************************************************************/

void	sigint_handler(int sig);
void	signals_setter(void);

#endif
