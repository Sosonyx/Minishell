/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedefs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:22:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/01 11:53:41 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_TYPEDEFS_H
# define MINISHELL_TYPEDEFS_H

/********************************************************************************/
/*			Enums																*/
/********************************************************************************/

typedef enum	e_error_status	t_error_status;
typedef enum 	e_toktype		t_toktype;
typedef enum 	e_redirtype		t_redirtype;
typedef enum	e_optype		t_op_type;

/********************************************************************************/
/*			Structures															*/
/********************************************************************************/

typedef struct	t_minishell		t_minishell;
typedef			t_minishell		*t_minishell_p;

typedef struct	s_arg			t_arg;
typedef 		t_arg			*t_arg_p;

typedef struct 	s_token			t_token;
typedef			t_token			*t_token_p;

typedef struct	s_leaf			t_leaf;
typedef 		t_leaf			*t_leaf_p;

typedef struct	s_redir			t_redir;
typedef			t_redir			*t_redir_p;

typedef struct 	s_ast			t_ast;
typedef			t_ast			*t_ast_p;
typedef			t_ast			t_sub_ast;
typedef			t_sub_ast		*t_sub_ast_p;

typedef struct	s_cntl_op		t_cntl_op;
typedef			t_cntl_op		*t_cntl_op_p;

#endif