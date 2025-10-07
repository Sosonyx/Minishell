/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedefs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:22:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEFS_H
# define MINISHELL_TYPEDEFS_H

/********************************************************************************/
/*			Enums																*/
/********************************************************************************/

typedef enum	e_return_status	t_return_status;
typedef enum 	e_toktype		t_toktype;
typedef enum 	e_redirtype		t_redirtype;
typedef enum	e_optype		t_op_type;
typedef enum	e_ast_branch	t_ast_branch;

/********************************************************************************/
/*			Structures															*/
/********************************************************************************/

typedef struct	s_minishell		t_shell;
typedef			t_shell		*t_shell_p;

typedef struct	s_tok_container	t_tok_container;
typedef 		t_tok_container	*t_tok_container_p;

typedef struct 	s_token			t_token;
typedef			t_token			*t_token_p;

typedef struct	s_leaf			t_leaf;
typedef 		t_leaf			*t_leaf_p;

typedef struct	s_redir			t_redir;
typedef			t_redir			*t_redir_p;

typedef struct 	s_ast			t_ast;
typedef			t_ast			*t_ast_p;

typedef struct	s_cntl_op		t_cntl_op;
typedef			t_cntl_op		*t_cntl_op_p;

typedef struct	s_exec_var		t_exec_var;
typedef			t_exec_var		*t_exec_var_p;

typedef struct	s_build_var 	t_build_var;
typedef struct	t_build_var		*t_build_var_p;;

#endif