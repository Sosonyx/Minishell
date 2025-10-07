/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/07 13:50:37 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_create_leaf(t_shell_p shell, t_ast_p *ast, t_build_var vars)
{
	t_leaf_p	new_leaf;

	(*ast)->leaf = _calloc(shell, 1, sizeof(struct s_leaf));
	new_leaf = (*ast)->leaf;
	if (new_leaf)
	{
		build_redir(shell, *ast, vars);
		if (is_no_abort(shell))
			build_cmd(shell, *ast, vars);
		if (is_no_abort(shell))
			input_heredoc(shell, new_leaf);
	}
	else
		free(*ast);
}

void	create_leaf(t_shell_p shell, t_ast_p *ast, t_build_var vars)
{
	if (is_no_abort(shell))
	{
		*ast = _calloc(shell, 1, sizeof(struct s_ast));
		if (*ast)
			_create_leaf(shell, ast, vars);
	}
}
