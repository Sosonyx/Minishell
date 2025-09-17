/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_ast.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 19:55:17 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/16 22:03:09 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	_destroy_ast(t_ast_p *ast)
{
	if ((*ast))
	{
		if ((*ast)->leaf)
		{
			ft_split_free((*ast)->leaf->cmds);
			free((*ast)->leaf->name);
			free((*ast)->leaf);
		}
		else
		{
			_destroy_ast(&(*ast)->cntl_op->left);
			free((*ast)->cntl_op->left);
			(*ast)->cntl_op->left = NULL;
			_destroy_ast(&(*ast)->cntl_op->right);
			(*ast)->cntl_op->right = NULL;
			free((*ast)->cntl_op->right);			
			free((*ast)->cntl_op);
			(*ast)->cntl_op = NULL;
		}
	}
}

void	destroy_ast(t_ast_p *ast)
{
/* 	if (*ast)
	{
		_destroy_ast(ast);
		free(*ast);
	}
	*ast = NULL; */
}
