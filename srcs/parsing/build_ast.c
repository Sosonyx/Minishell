/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:02:23 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/04 18:05:34 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// static int	look_forward_next_token(t_tok_container_p tok_container, int start, int end)
// {
// 	while (start <= end)
// 	{
// 		if (tok_container->tokens[start])
// 			break ;
// 		start++;
// 	}
// 	return (start);
// }

// static int	set_end(t_tok_container_p tok_container, int *end, t_ast_branch branch, int first)
// {
// 	while (tok_container->tokens && tok_container->tokens[*end])
// 		(*end)++;

// 	if (branch == LEFT_BRANCH && !first)
// 		return (tok_container->op_index - 1);
// 	else
// 		return (*end);
// }

// void	build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, t_ast_branch branch, int first)
// {
//     int subshell = 0;
//     int end_index;
//     int last;
	
// 	end_index = set_end(tok_container, &end, branch, first);
// 	if (!parse_cntl_and_or(ast, tok_container, start, end_index))
// 	{
// 		if (!parse_cntl_pipe(ast, tok_container, start, end_index))
// 		{
// 			if (!parse_subshell(ast, tok_container, start, end))
// 			{
// 				if (!create_leaf(ast, tok_container, start, end))
// 					; // kill_shell();
// 				else
// 					return ;
// 			}
// 			else
// 				subshell = 1;
// 		}
// 	}
// 	if (!subshell && *ast)
// 	{
// 		(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
// 		if ((*ast)->cntl_op)
// 		{
// 			if (!subshell)
// 				build_ast(&(*ast)->cntl_op->left, tok_container, start, tok_container->op_index - 1, LEFT_BRANCH, 0);			
// 			build_ast(&(*ast)->cntl_op->right, tok_container, tok_container->op_index + 1, end, RIGHT_BRANCH, 0);
// 		}
// 		else
// 			;	// kill_shell();
// 	}
// 	start = look_forward_next_token(tok_container, start, end_index);
// 	if (start < end_index)
// 		build_ast(&(*ast)->cntl_op->right, tok_container, start, end, RIGHT_BRANCH, 0);
// }


static int	set_end(t_tok_container_p tok_container, int *end, t_ast_branch branch, int first)
{
    if (first)
    {
        *end = 0;
        while (tok_container->tokens && tok_container->tokens[*end])
            (*end)++;
        (*end)--;
    }
    if (branch == LEFT_BRANCH && !first)
        return (tok_container->op_index - 1);
    return (*end);
}

// void	build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, t_ast_branch branch, int first)
// {
//     int	subshell;

//     subshell = 0;
//     set_end(tok_container, &end, branch, first);
//     if (!parse_cntl_and_or(ast, tok_container, start, end))
//     {
//         if (!parse_cntl_pipe(ast, tok_container, start, end))
//         {
//             if (!parse_subshell(ast, tok_container, start, end))
//             {
//                 if (create_leaf(ast, tok_container, start, end) == RETURN_FAIL)
//                     ; // kill_shell();
//                 else
//                     return ;
//             }
//             else
//                 subshell = 1;
//         }
//     }
//     if (*ast)
//     {
//         (*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
//         if (!(*ast)->cntl_op)
//             ; // kill_shell();
//         build_ast(&(*ast)->cntl_op->left, tok_container,
//             start, tok_container->op_index - 1, LEFT_BRANCH, 0);
//         if (!subshell)
//             build_ast(&(*ast)->cntl_op->right, tok_container,
//                 tok_container->op_index + 1, end, RIGHT_BRANCH, 0);
//     }
// }

void	build_ast(t_ast_p *ast, t_tok_container_p tok_container, int start, int end, t_ast_branch branch, int first)
{
	int		subshell;
	int		op_pos;
	int	 	left_end;
	int		right_end;
	int		right_start;
	
	subshell = 0;
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
	if (!parse_cntl_and_or(ast, tok_container, start, end))
	{
		if (!parse_cntl_pipe(ast, tok_container, start, end))
		{
			if (!parse_subshell(ast, tok_container, start, end))
			{
				if (create_leaf(ast, tok_container, start, end) == RETURN_FAIL)
					; // kill_shell()
				else
					return ;
			}
			else
				subshell = 1;
		}
	}
	if (*ast)
	{
		(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
		if (!(*ast)->cntl_op)
			; // kill_shell()
		op_pos = tok_container->op_index;
		left_end = op_pos - 1;
		while (left_end >= start && !tok_container->tokens[left_end])
			left_end--;
		if (left_end >= start)
			build_ast(&(*ast)->cntl_op->left, tok_container,
				start, left_end, LEFT_BRANCH, 0);
		if (!subshell)
		{
			right_start = op_pos + 1;
			while (right_start <= end && !tok_container->tokens[right_start])
				right_start++;
			right_end = end;
			while (right_end >= right_start && !tok_container->tokens[right_end])
				right_end--;
			if (right_start <= right_end)
				build_ast(&(*ast)->cntl_op->right, tok_container, right_start, right_end, RIGHT_BRANCH, 0);
		}
	}
}
