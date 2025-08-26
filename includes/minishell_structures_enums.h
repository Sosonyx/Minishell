/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/08/25 19:29:19 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTURES_ENUMS_H
# define MINISHELL_STRUCTURES_ENUMS_H

# include "minishell.h"

/********************************************************************************/
/*			Enums																*/
/********************************************************************************/

enum e_toktype
{
	T_WORD,
	T_PIPE,
	T_REDIR_IN,
	T_REDIR_OUT,
	T_APPEND,
	T_HEREDOC,
	T_AND,
	T_OR,
	T_LPARENT,
	T_RPARENT,
	T_EXPAND,
};

enum e_redirtype
{ 
	R_IN,
	R_OUT,
	R_APP,
	R_HDOC,
	R_AND,
	R_OR
};

/********************************************************************************/
/*			Structures															*/
/********************************************************************************/

struct s_token
{
	t_toktype		type;
	char			*val;
	bool			was_single_quoted; 		// pour heredoc (si delim etait quote)
	bool			was_double_quoted; 		// on autorise l expansion
};

struct s_arg
{
	char			**redir_in; 			// NULL terminated
	char			**cmd_plus_args; 		// [0] == cmd et NULL terminated
	char			**redir_out;			// NULL terminated
	t_toktype		type_of_redirection;
	t_token			**cmds;					// pas pour l'exec
	t_arg_p			next;
}; 

//	structure a transmettre pour l'exec
struct s_exec_line
{
	char			**redir_in; 			// NULL terminated
	char			**cmd_plus_args; 		// [0] == cmd et NULL terminated
	char			**redir_out;			// NULL terminated
	t_toktype		type_of_redirection;
	t_exec_line_p	next;
}; 

#endif
