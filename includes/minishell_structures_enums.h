/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/08/27 13:18:55 by ihadj            ###   ########.fr       */
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
	OP_PIPE,
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

// one command at a time
struct s_redir
{
	enum e_redirtype	type;
	char				*target;
	struct s_redir		*next;
};

struct s_leaf
{
	char				**cmd_plus_args;
	t_redir_p			redir;					// tableau de redirs in et de redirs out 
	t_leaf_p			next;					// pointeur vers le bloc suivant  a executer 
	bool				is_builtin;				// 0/1 ou petit enum
};

/// AST
struct s_branching
{
	t_sub_ast			left;
	t_sub_ast			right;
};

struct	s_ast
{
	t_leaf_p			leaf;

	t_optype			type;
	t_branching_p		branching;	
};

#endif
