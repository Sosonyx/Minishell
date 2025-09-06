/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/18 12:48:48 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/05 17:50:23 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _GNU_SOURCE

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/stat.h>
# include <signal.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <errno.h>

# include "minishell_typedefs.h"
# include "minishell_structures_enums.h"
# include "minishell_parsing.h"
// # include "minishell_exec.h"

# include "libft.h"

# define PROMPT_MESSAGE "\001\033[48;5;57m\002minishell>\001\033[0m\002 "

#endif
