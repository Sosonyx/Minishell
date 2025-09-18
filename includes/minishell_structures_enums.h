/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 12:59:31 by ihadj            ###   ########.fr       */
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

enum e_return_status
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
	R_IN = 1,
	R_OUT = 2,
	R_APPEND = 4,
	R_HDOC = 8,
};

enum e_optype
{
	OP_PIPE = 1,
	OP_AND = 2,
	OP_OR = 4,
	OP_SUBSHELL = 8,
	OP_LEAF = 16
};

enum e_process
{
	CHILD = 1,
	PARENT = 2
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



// toutes les redirections IN et OUT chainees
struct s_redir
{
	enum e_redirtype	type;
	char				*target;
	char				*limiter;
	int					fd;
	struct s_redir		*next;
};

struct s_leaf
{
	pid_t				pid;

	char				**cmds;
	char				*name;
	t_redir_p			redir;
	
	int					fds[2];
	int					hd_fd[2];
	
	bool				r_in;
	char				*r_in_path;
	bool				r_out;
	char				*r_out_path;

	bool				configured;

	bool				abort;
};

struct s_cntl_op
{
	t_op_type  		op;
	t_ast_p			left;
	t_ast_p			right;
};

struct	s_ast
{
	t_leaf_p			leaf;

	t_op_type			type;
	t_cntl_op_p			cntl_op;

	int					*cur_pipe;
	
	int					*read_fd;
	int					*write_fd;
};

struct s_minishell
{
	int				ac;
	char			**av;
	char			**environ;
	int				readlines;
	char			*input;
};

#endif

