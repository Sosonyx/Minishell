/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_subshell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:22:45 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/17 20:09:51 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	parse_subshell(t_minishell_p shell, t_ast_p *op, t_tok_container_p tok_container, int start, int end)
{
	int	n;
	int	subshell_end;

	subshell_end = 0;
	n = 0;
	if (tok_container->tokens[start] && (tok_container->tokens[start])->type == T_LPARENT)
	{
		subshell_end = end;
		while (subshell_end >= 0 && subshell_end > start)
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
			(*op)->type = OP_SUBSHELL;
			free(tok_container->tokens[start]);
			tok_container->tokens[start] = NULL;
			free(tok_container->tokens[subshell_end]);
			tok_container->tokens[subshell_end] = NULL;
			(*op)->cntl_op = ft_calloc(1, sizeof(struct s_cntl_op));
			if ((*op)->cntl_op)
			{
				build_ast(shell, &(*op)->cntl_op->left, tok_container, ++start, subshell_end - 1, LEFT_BRANCH, 0);
				return (RETURN_OK);
			}			
		}
	}
	return (RETURN_FAIL);	
}
