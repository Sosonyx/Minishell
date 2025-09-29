/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:02:23 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 16:59:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	reset_global_end(int first, int start, int end, t_tok_container_p tok_container)
{
	if (first)
	{
		end = 0;
		while (tok_container->tokens && tok_container->tokens[end])
			end++;
		end--;
	}
	else
	{
		while (end >= start && !tok_container->tokens[end])
			end--;
	}
	return (end);
}

static int	get_left_end(int start, int op_pos, t_tok_container_p tok_container)
{
	int left_end;

	left_end = op_pos - 1;
	while (left_end >= start && !tok_container->tokens[left_end])
		left_end--;
	return (left_end);
}

static int	get_right_limits(int op_pos, int end, t_tok_container_p tok_container, int *right_start)
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

void	build_ast(t_minishell_p shell, t_ast_p *ast, int start, int end, t_ast_branch branch, int first)
{
	int	op_pos;
	int	left_end;
	int	right_start;
	int	right_end;

	end = reset_global_end(first, start, end, shell->tokens);
	if (!parse_cntl_and_or(shell, ast, start, end) && !parse_cntl_pipe(shell, ast, start, end) && !parse_subshell(shell, ast, start, end))
	{
		if (create_leaf(shell, ast, start, end) == RETURN_FAIL)
			; // kill_shell()
		else
			return ;
	}
	if (*ast && (*ast)->type != OP_SUBSHELL)
	{
		if ((*ast)->type == OP_SUBSHELL)
			return ;
		(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
	if (!(*ast)->cntl_op)
		; // kill_shell()
	op_pos = shell->tokens->op_index;
	left_end = get_left_end(start, op_pos, shell->tokens);
	if (start <= left_end)
		build_ast(shell, &(*ast)->cntl_op->left, start, left_end, LEFT_BRANCH, 0);
	right_end = get_right_limits(op_pos, end, shell->tokens, &right_start);
	if (right_start <= right_end)
		build_ast(shell, &(*ast)->cntl_op->right, right_start, right_end, RIGHT_BRANCH, 0);
	}
}
