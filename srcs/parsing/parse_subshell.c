/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/04 17:27:24 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_error_status	parse_subshell(t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	int			n = 0;
	int			subshell_end = 0;

	if (tok_container->tokens[start] && (tok_container->tokens[start])->type == T_LPARENT)
	{
		subshell_end = end;
		while (subshell_end > start)
        {
			if ((!tok_container->tokens[subshell_end]))
				subshell_end--;
			else if ((tok_container->tokens[subshell_end]->type != T_RPARENT))
				subshell_end--;
			else
				break ;
		}
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
				build_ast(&(*op)->cntl_op->left, tok_container, ++start, subshell_end - 1, LEFT_BRANCH, 0);
				return (RETURN_OK);
			}			
		}
	}
	return (RETURN_FAIL);	
}
