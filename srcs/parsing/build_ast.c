/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_ast.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 12:02:23 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 19:31:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	init_global_end(struct s_build_var vars, t_tok_container_p tok_container)
{
	vars.end = 0;
	while (tok_container->tokens && tok_container->tokens[vars.end])
		vars.end++;
	vars.end--;
	return (vars.end);
}

static int	reset_global_end(struct s_build_var vars, t_tok_container_p tok_container)
{
	while (vars.end >= vars.start && !tok_container->tokens[vars.end])
		vars.end--;
	return (vars.end);
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

static int	_seek_cntl_op(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	if (parse_cntl_and_or(shell, ast, vars.start, vars.end))
		return (RETURN_OK);
	else if (parse_cntl_pipe(shell, ast, vars.start, vars.end))
		return (RETURN_OK);
	else if (parse_subshell(shell, ast, vars))
		return (RETURN_OK);
	else
		return (RETURN_FAIL);
}

void	_build_ast(t_minishell_p shell, t_ast_p *ast, t_build_var vars, t_ast_branch branch)
{
	vars.end = reset_global_end(vars, shell->tokens);

	if (_seek_cntl_op(shell, ast, vars))
	{
		if (*ast && (*ast)->type != OP_SUBSHELL)
		{
			(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
			if (!(*ast)->cntl_op)
				; // kill_shell()
				if (!(*ast)->cntl_op)
					; // kill_shell()
				vars.op_pos = shell->tokens->op_index;
				vars.left_end = get_left_end(vars.start, vars.op_pos, shell->tokens);
				if (vars.start <= vars.left_end)
					_build_ast(shell, &(*ast)->cntl_op->left, (struct s_build_var) {vars.start, vars.left_end}, LEFT_BRANCH);
				vars.right_end = get_right_limits(vars.op_pos, vars.end, shell->tokens, &vars.right_start);
				if (vars.right_start <= vars.right_end)
					_build_ast(shell, &(*ast)->cntl_op->right, (struct s_build_var) {vars.right_start, vars.right_end}, RIGHT_BRANCH);
		}
	}
	else
		create_leaf(shell, ast, vars.start, vars.end);
}

void	_init_ast(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	vars.end = init_global_end(vars, shell->tokens);

	if (_seek_cntl_op(shell, ast, vars))
	{
		if (*ast && (*ast)->type != OP_SUBSHELL)
		{
			(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
			if (!(*ast)->cntl_op)
				; // kill_shell()
				if (!(*ast)->cntl_op)
					; // kill_shell()
				vars.op_pos = shell->tokens->op_index;
				vars.left_end = get_left_end(vars.start, vars.op_pos, shell->tokens);
				if (vars.start <= vars.left_end)
					_build_ast(shell, &(*ast)->cntl_op->left, (struct s_build_var) {vars.start, vars.left_end}, LEFT_BRANCH);
				vars.right_end = get_right_limits(vars.op_pos, vars.end, shell->tokens, &vars.right_start);
				if (vars.right_start <= vars.right_end)
					_build_ast(shell, &(*ast)->cntl_op->right, (struct s_build_var) {vars.right_start, vars.right_end}, RIGHT_BRANCH);
		}
	}
	else
		create_leaf(shell, ast, vars.start, vars.end);
}

void	build_ast(t_minishell_p shell, t_ast_p *ast)
{
	_init_ast(shell, ast, (struct s_build_var) {0});
}


// static int	reset_global_end(int first, struct s_build_var vars, t_tok_container_p tok_container)
// {
// 	if (first)
// 	{
// 		vars.end = 0;
// 		while (tok_container->tokens && tok_container->tokens[vars.end])
// 			vars.end++;
// 		vars.end--;
// 	}
// 	else
// 	{
// 		while (vars.end >= vars.start && !tok_container->tokens[vars.end])
// 			vars.end--;
// 	}
// 	return (vars.end);
// }

// static int	get_left_end(int start, int op_pos, t_tok_container_p tok_container)
// {
// 	int left_end;

// 	left_end = op_pos - 1;
// 	while (left_end >= start && !tok_container->tokens[left_end])
// 		left_end--;
// 	return (left_end);
// }

// static int	get_right_limits(int op_pos, int end, t_tok_container_p tok_container, int *right_start)
// {
// 	int	right_end;

// 	right_end = end;
// 	*right_start = op_pos + 1;
// 	while (*right_start <= end && !tok_container->tokens[*right_start])
// 		(*right_start)++;
// 	while (right_end >= *right_start && !tok_container->tokens[right_end])
// 		right_end--;
// 	return (right_end);
// }

// static int	_seek_cntl_op(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
// {
// 	if (parse_cntl_and_or(shell, ast, vars.start, vars.end))
// 		return (RETURN_OK);
// 	else if (parse_cntl_pipe(shell, ast, vars.start, vars.end))
// 		return (RETURN_OK);
// 	else if (parse_subshell(shell, ast, vars))
// 		return (RETURN_OK);
// 	else
// 		return (RETURN_FAIL);
// }

// void	_build_ast(t_minishell_p shell, t_ast_p *ast, t_build_var vars, t_ast_branch branch, int first)
// {
// 	vars.end = reset_global_end(first, vars, shell->tokens);

// 	if (_seek_cntl_op(shell, ast, vars))
// 	{
// 		if (*ast && (*ast)->type != OP_SUBSHELL)
// 		{
// 			(*ast)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
// 			if (!(*ast)->cntl_op)
// 				; // kill_shell()
// 				if (!(*ast)->cntl_op)
// 					; // kill_shell()
// 				vars.op_pos = shell->tokens->op_index;
// 				vars.left_end = get_left_end(vars.start, vars.op_pos, shell->tokens);
// 				if (vars.start <= vars.left_end)
// 					_build_ast(shell, &(*ast)->cntl_op->left, (struct s_build_var) {vars.start, vars.left_end}, LEFT_BRANCH, 0);
// 				vars.right_end = get_right_limits(vars.op_pos, vars.end, shell->tokens, &vars.right_start);
// 				if (vars.right_start <= vars.right_end)
// 					_build_ast(shell, &(*ast)->cntl_op->right, (struct s_build_var) {vars.right_start, vars.right_end}, RIGHT_BRANCH, 0);
// 		}
// 	}
// 	else
// 		create_leaf(shell, ast, vars.start, vars.end);
// }

// void	build_ast(t_minishell_p shell, t_ast_p *ast)
// {
// 	_build_ast(shell, ast, (struct s_build_var) {0}, AST_INIT, 1);
// }
