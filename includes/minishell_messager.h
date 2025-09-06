/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_messager.h                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 14:05:48 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/06 16:42:01 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_MESSAGER_H
# define MINISHELL_MESSAGER_H

# ifdef NEWLINE
#  undef NEWLINE
#   define NEWLINE "\n"
# endif

# define SELF "Minishell: "
# define COLUMN ": "

void	self_speak(int fd, char *announce, char *separator, bool announce_self)__attribute__((nonnull));

#endif
