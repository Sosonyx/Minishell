/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/08/27 17:25:10 by cgajean          ###   ########.fr       */
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


typedef struct s_arg
{
	t_token	**cmds;
	char	**args;
	int		oldfd[2];
	int		nextfd[2];
	int		ac;
}	t_arg;

///
///	parsing
///
struct s_token
{
	t_toktype			type;
	char				*val;
	bool				was_single_quoted;		// pour heredoc (si delim etait quote)
	bool				was_double_quoted;		// on autorise l expansion
	bool				expandable;
};


// toutes les redirections IN et OUT chainees
struct s_redir
{
	enum e_redirtype	type;
	char				*target;
	struct s_redir		*next; //pointeur vers la redir suivante
};

struct s_leaf
{
	char				**cmds;
	t_redir_p			redir;					// tableau de redirs in et de redirs out 
	t_leaf_p			next;					// pointeur vers le bloc suivant  a executer 
	bool				is_builtin;				// 0/1 ou petit enum
};

///
/// AST
///

		// control operator
		// 	A token that performs a control function. It is one of the following symbols: 
		// 	|| & && ; ;; ( ) | |& <newline> 
		
struct s_cntl_op
{
	t_sub_ast_p			left;
	t_sub_ast_p			right;					// si SUBSHELL pas de right
};

struct	s_ast
{
	t_leaf_p			leaf;

	t_op_type			type;
	t_cntl_op_p			cntl_op;	
};


#endif

