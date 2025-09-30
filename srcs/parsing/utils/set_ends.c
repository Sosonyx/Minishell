/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_global_ends.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 20:02:18 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 20:02:48 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_global_end(t_build_var vars, t_tok_container_p tok_container)
{
	vars.end = 0;
	while (tok_container->tokens && tok_container->tokens[vars.end])
		vars.end++;
	vars.end--;
	return (vars.end);
}

int	set_global_end(t_build_var vars, t_tok_container_p tok_container)
{
	while (vars.end >= vars.start && !tok_container->tokens[vars.end])
		vars.end--;
	return (vars.end);
}

int	set_left_end(int start, int op_pos, t_tok_container_p tok_container)
{
	int left_end;

	left_end = op_pos - 1;
	while (left_end >= start && !tok_container->tokens[left_end])
		left_end--;
	return (left_end);
}

int	set_right_end(int op_pos, int end, t_tok_container_p tok_container, int *right_start)
{
	int	right_end;

	right_end = end;
	*right_start = op_pos + 1;
	while (*right_start <= end && !tok_container->tokens[*right_start])
		(*right_start)++;
	while (right_end >= *right_start && !tok_container->tokens[right_end])
		right_end--;
	return (right_end);
}
