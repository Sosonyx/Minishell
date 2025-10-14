/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_and_signal_manager.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:26:32 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 14:47:43 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef MINISHELL_ERROR_AND_SIGNAL_MANAGER_H
# define MINISHELL_ERROR_AND_SIGNAL_MANAGER_H

/*	Error messages	*/
# define CMD_ERRMSG			"command not found"
# define MEM_ERRMSG			"Memory error. Restart Minishell."
# define PIP_ERRMSG			"Pipe error. Restart Minishell."
# define FORK_ERRMSG			"Fork error. Restart Minishell."
# define AST_ERRMSG			"Execution failed. Restart Minishell."
# define DUP_ERRMSG			"Dup error. Restart Minishell."
# define DUP2_ERRMSG			"Dup2 error. Restart Minishell."
# define ARG_EXCESS_ERRMSG	"too many arguments"
# define ARG_NON_NUM_ERRMSG	"numeric argument required"
# define INVALID_ID_ERRMSG	"not a valid identifier"
# define AMBIG_REDIR_ERRMSG	"ambiguous redirect"
# define ER		"minishell: unexpected EOF while looking for matching quote\n"

/*	Separators		*/
# ifdef 	NEWLINE
#  undef 	NEWLINE
#  define NEWLINE		"\n"
# endif

# define COLUMN		": "
# define NOSEP		""

/*	Return values	*/
# define ERRVAL1		256
# define ERRVAL2		512

/*****************************************************************************/
/*			Errors															 */
/*****************************************************************************/
void	speak(t_shell_p shell, int fd, char *announce, char *separator);
void	speak2(t_shell_p shell, int fd, char **announces);
void	print_file_error(t_shell_p shell, char *filename, int err_num);
void	print_cmd_error(t_shell_p shell, char *cmd_name, int err_num);
void	print_cmd_error2(t_shell_p shell, char *cmd_name, char *errmsg);
void	print_generic_error(t_shell_p shell, char *errmsg);
void	print_generic_error2(t_shell_p shell, char **errmsg);
void	print_hd_error(t_shell_p shell, char *limiter);
void	set_abort(t_shell_p shell, char *errmsg);
bool	is_no_abort(t_shell_p shell);

/*****************************************************************************/
/*			Signals															 */
/*****************************************************************************/

void	sigint_handler(int sig);
void	signals_setter(void);
void	signals_ign(void);
void	signals_dfl(void);
void	sigint_handler_exec(int sig);
void	signals_setter_exec(void);
void	handle_signal_error(t_shell_p shell);

#endif
