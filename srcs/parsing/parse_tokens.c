/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 14:10:20 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/16 21:17:59 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_tokens(t_ast_p *ast, t_tok_container_p tok_container)
{
	if (ast)
	{
		build_ast(ast, tok_container, 0, 0, AST_INIT, 1);
		if (*ast)
		{
			return (RETURN_OK);
		}
	}
	return (RETURN_FAIL);
}
