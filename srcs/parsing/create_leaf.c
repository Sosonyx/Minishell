/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/29 16:41:00 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	_create_leaf(t_minishell_p shell, t_ast_p *ast, int start, int end)
{
	t_leaf_p	new_leaf;
	
	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
	new_leaf = (*ast)->leaf;
	if (new_leaf)
	{
		new_leaf->redir = build_redir(shell->tokens, start, end);
		build_cmd(&new_leaf->cmds, shell->tokens, start, end);
		input_heredoc(shell, new_leaf);
	}
	else
	{
		free(*ast);
		set_abort(shell, MEM_ERRMSG);
	}	
}

int	create_leaf(t_minishell_p shell, t_ast_p *ast, int start, int end)
{
	*ast = ft_calloc(1, sizeof(struct s_ast));
	if (*ast)
	{	
		_create_leaf(shell, ast, start, end);
	}
	else
	{
		set_abort(shell, MEM_ERRMSG);
	}
	return (shell->abort == false);
}
