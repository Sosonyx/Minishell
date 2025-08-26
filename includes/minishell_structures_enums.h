/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/08/26 19:32:03 by cgajean          ###   ########.fr       */
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
	R_APPEND,
	R_HDOC,
};

enum e_optype
{
	// OP_PIPE,
	OP_AND,
	OP_OR,
	OP_SUBSHELL
};

/********************************************************************************/
/*			Structures															*/
/********************************************************************************/

///	parsing
struct s_token
{
	t_toktype			type;
	char				*val;
	bool				was_single_quoted;		// pour heredoc (si delim etait quote)
	bool				was_double_quoted;		// on autorise l expansion
	bool				expandable;
};

/// one command at a time
struct s_redir
{
	enum e_redirtype	type;
	char				*target;
	struct s_redir		*next;
};

struct s_exec_line
{
	char				**cmd_plus_args;
	t_redir_p			redir;					// tableau de redirs in et de redirs out 
	t_exec_line_p		next;					// pointeur vers le bloc suivant  a executer 
	bool				is_builtin;				// 0/1 ou petit enum
};

/// AST
struct s_binop
{
	t_operator_p		left; 
	t_operator_p		right;
};

union	u_node
{
	t_binop				binop;					// binary operation (OR et AND)
	t_exec_line			exec_line;
};

struct s_operator
{
	t_optype			type;
	t_node				node;
	t_operator			next;
};

#endif
