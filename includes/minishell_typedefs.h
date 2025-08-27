/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedefs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:22:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/08/27 12:43:51 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEFS_H
# define MINISHELL_TYPEDEFS_H

typedef struct 	s_token			t_token;
typedef			t_token			*t_token_p;

typedef struct 	s_arg			t_arg;
typedef			t_arg			*t_arg_p;

typedef enum 	e_toktype		t_toktype;

typedef enum 	e_redirtype		t_redirtype;

typedef struct	s_leaf			t_leaf;
typedef 		t_leaf			*t_leaf_p;

typedef struct	s_redir			t_redir;
typedef			t_redir			*t_redir_p;

typedef enum	e_optype		t_optype;

typedef struct 	s_ast			t_ast;
typedef			t_ast			*t_ast_p;
typedef			t_ast			t_sub_ast;

typedef struct	s_branching		t_branching;
typedef			t_branching		t_branching_p;
/* typedef			t_branching		t_binop;
typedef			t_binop			*t_binop_p;
typedef			t_branching		t_subshell;
typedef			t_subshell		*t_subshell_p;
typedef			t_branching		t_pipe;
typedef			t_pipe			t_pipe_p; */

/* typedef union	u_node			t_node;
typedef			t_node			*t_node_p; */

#endif