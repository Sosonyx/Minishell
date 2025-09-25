/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_leaf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:04:07 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/25 11:28:57 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_leaf(t_minishell_p shell, t_ast_p *ast, t_tok_container_p tok_container, int start, int end)
{
	*ast = ft_calloc(1, sizeof(struct s_ast));
	if (!*ast)
		return (RETURN_FAIL);
	(*ast)->leaf = ft_calloc(1, sizeof(struct s_leaf));
	if (!(*ast)->leaf)
		return (RETURN_FAIL);
	(*ast)->leaf->redir = build_redir(tok_container, start, end);
	input_heredoc(shell, (*ast)->leaf);
	build_cmd(&(*ast)->leaf->cmds, tok_container, start, end);
	return (RETURN_OK);
}
