/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/04 15:26:39 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTURES_ENUMS_H
# define MINISHELL_STRUCTURES_ENUMS_H

# include "minishell.h"

/********************************************************************************/
/*			Enums																*/
/********************************************************************************/

enum e_ast_branch
{
	AST_INIT = 0,
	LEFT_BRANCH	= 1,
	RIGHT_BRANCH = 2
};

enum e_error_status
{
	RETURN_FAIL = 0,
	RETURN_OK = 1,
};

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
	T_INCORRECT,
	T_TARGET
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
	OP_PIPE = 1,
	OP_AND = 2,
	OP_OR = 4,
	OP_SUBSHELL = 8,
	OP_LEAF = 16
};

/********************************************************************************/
/*			Structures															*/
/********************************************************************************/

struct s_tok_container
{
	t_token		**tokens;
	char		**args;

	int			start_index;
	int			end_index;
	int			op_index;
	// int			oldfd[2];		// a garder ?
	// int			nextfd[2];		// a garder ?
	// int			ac;				// a garder ?
};

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

// struct s_minishell
// {
// 	t_ast_p	ast;
// 	t_tok_container_p	input;
// };

// toutes les redirections IN et OUT chainees
struct s_redir
{
	enum e_redirtype	type;
	char				*target;
	char				*limiter;
	struct s_redir		*next;					//pointeur vers la redir suivante
};

struct s_leaf
{
	char				**cmds;
	t_redir_p			redir;					// tableau de redirs in et de redirs out 
	// t_leaf_p			next;					// pointeur vers le bloc suivant  a executer 
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
	// t_op_type   op;
	t_ast_p			left;
	t_ast_p			right;					// si SUBSHELL pas de right
};

struct	s_ast
{
	t_leaf_p			leaf;

	t_op_type			type;
	t_cntl_op_p			cntl_op;
};

#endif

