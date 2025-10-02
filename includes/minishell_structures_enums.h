/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_structures_enums.h                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:02:21 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/02 16:32:23 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_STRUCTURES_ENUMS_H
# define MINISHELL_STRUCTURES_ENUMS_H

# include "minishell.h"

/********************************************************************************/
/*			Enums																*/
/********************************************************************************/

enum e_return_status
{
	RETURN_FAIL = 0,
	RETURN_OK = 1,
};

enum e_toktype
{
	T_WORD = 1,
	T_PIPE = 2,
	T_REDIR_IN = 4,
	T_REDIR_OUT = 8,
	T_APPEND = 16,
	T_HEREDOC = 32,
	T_AND = 64,
	T_OR = 128,
	T_LPARENT = 256,
	T_RPARENT = 512,
	T_INCORRECT = 1024,
	T_TARGET = 2048
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
	bool				was_single_quoted;
	bool				was_double_quoted;
	bool				expandable;
};

struct s_build_var
{
	int	start;
	int	end;
	int	op_pos;
	int	left_end;
	int	right_start;
	int	right_end;
	int	i;
};

typedef struct s_expanded
{
	char	*value;
	bool	split_allowed;
}	t_expanded;


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
	char				*full_path;
	char				*exec_path;
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
	int					*closed_fd;
};

struct s_minishell
{
	char				*name;
	int					ac;
	char				**av;
	char				**environ;
	int					readlines;
	char				*input;
	int					std_fds[3];
	bool				abort;
	int					exit_code;

	t_tok_container_p	tokens;
};

#endif

