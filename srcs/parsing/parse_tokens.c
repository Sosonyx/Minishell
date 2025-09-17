/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/17 20:11:30 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_tokens(t_minishell_p shell, t_ast_p *ast, t_tok_container_p tok_container)
{
	if (ast)
	{
		build_ast(shell, ast, tok_container, 0, 0, AST_INIT, 1);
		if (*ast)
		{
			return (RETURN_OK);
		}
	}
	return (RETURN_FAIL);
}
