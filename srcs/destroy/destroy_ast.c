/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:55:17 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 14:04:31 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_destroy_ast(t_ast_p *ast)
{
	if (!ast || !*ast)
		return ;
	if ((*ast)->leaf)
		destroy_leaf((*ast));
	else
	{
		if ((*ast)->cntl_op)
		{
			if ((*ast)->cntl_op->left)
				_destroy_ast(&(*ast)->cntl_op->left);
			if ((*ast)->cntl_op->right)
				_destroy_ast(&(*ast)->cntl_op->right);
			free((*ast)->cntl_op);
		}
	}
	free(*ast);
	*ast = NULL;
}

void	destroy_ast(t_ast_p *ast)
{
	if (!ast || !*ast)
		return ;
	_destroy_ast(ast);
}
