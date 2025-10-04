/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/03 16:50:50 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_create_leaf(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	t_leaf_p	new_leaf;

	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
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
	{
		free(*ast);
		set_abort(shell, MEM_ERRMSG);
	}	
}

int	create_leaf(t_minishell_p shell, t_ast_p *ast, t_build_var vars)
{
	*ast = ft_calloc(1, sizeof(struct s_ast));
	if (*ast)
	{	
		_create_leaf(shell, ast, vars);
	}
	else
	{
		set_abort(shell, MEM_ERRMSG);
	}
	return (shell->abort == false);
}
