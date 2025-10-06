/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_type.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/04 16:27:02 by sosony            #+#    #+#             */
/*   Updated: 2025/10/04 16:27:03 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_pipe(t_toktype t)
{
	return (t == T_PIPE);
}

int	is_control_op(t_toktype t)
{
	return (((t == T_AND) || is_pipe(t) || (t == T_OR)));
}
