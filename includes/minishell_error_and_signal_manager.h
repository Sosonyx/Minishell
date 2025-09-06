/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_error_and_signal_manager.h               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:37:01 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 16:38:41 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#ifndef MINISHELL_ERROR_AND_SIGNAL_MANAGER_H
# define MINISHELL_ERROR_AND_SIGNAL_MANAGER_H

# define FILE_ERRMSG "No such file or directory"
# define CMD_ERRMSG "command not found"

/********************************************************************************/
/*			Errors																*/
/********************************************************************************/

void	print_file_error(char *filename)__attribute__((nonnull));
void	print_cmd_error(char *cmd_name)__attribute__((nonnull));
void	print_generic_error(char *errmsg)__attribute__((nonnull));

/********************************************************************************/
/*			Signals																*/
/********************************************************************************/

void	sigint_handler(int sig);
void	signals_setter(void);

#endif
