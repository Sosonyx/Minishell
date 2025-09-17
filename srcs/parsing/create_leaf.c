/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/17 13:07:05 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



int	create_leaf(t_ast_p *ast, t_tok_container_p tok_container, int start, int end)
{
	*ast = ft_calloc(1, sizeof(t_ast));
	if (!*ast)
		return (RETURN_FAIL);
	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
	if (!(*ast)->leaf)
		return (RETURN_FAIL);
/* 	(*ast)->leaf->fds[0] = -2;
	(*ast)->leaf->fds[1] = -2; */
	(*ast)->leaf->redir = build_redir(tok_container, start, end);
	build_cmd(&(*ast)->leaf->cmds, tok_container, start, end);
	return (RETURN_OK);
}
