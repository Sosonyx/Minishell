/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/04 12:23:58 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_status	parse_subshell(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	int			n = 0;
	int			subshell_end = 0;

	if (tok_container->tokens[start] && (tok_container->tokens[start])->type == T_LPARENT)
	{
		subshell_end = end - 1;
		while (tok_container->tokens[subshell_end] && tok_container->tokens[subshell_end]->type != T_RPARENT && subshell_end <= end)
			subshell_end--;
		*op = ft_calloc(1, sizeof(t_ast));
		if (*op)
		{
			// tok_container->op_index++;
			(*op)->type = OP_SUBSHELL;
			free(tok_container->tokens[start]);
			tok_container->tokens[start] = NULL;
			free(tok_container->tokens[subshell_end]);
			tok_container->tokens[subshell_end] = NULL;
			(*op)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
			if ((*op)->cntl_op)
			{
				build_ast(&(*op)->cntl_op->left, tok_container, ++start, subshell_end, LEFT_BRANCH, 1);
				return (RETURN_OK);
			}			
		}
	}
	return (RETURN_FAIL);	
}
