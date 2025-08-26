/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_typedefs.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/25 19:22:09 by cgajean           #+#    #+#             */
/*   Updated: 2025/08/25 19:28:33 by cgajean          ###   ########.fr       */
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
typedef struct	s_exec_line		t_exec_line;
typedef 		t_exec_line		*t_exec_line_p;

#endif