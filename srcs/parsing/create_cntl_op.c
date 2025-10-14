/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cntl_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:34:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/14 16:51:24 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_cntl_op(t_shell_p shell, t_ast_p *op, t_toktype type)
{
	if (is_no_abort(shell))
	{
		*op = _calloc(shell, 1, sizeof(t_ast));
		set_is_root(shell, op);
		if (*op)
		{
			if (type == T_AND)
				(*op)->type = OP_AND;
			if (type == T_OR)
				(*op)->type = OP_OR;
			if (type == T_PIPE)
				(*op)->type = OP_PIPE;
			if (type == T_LPARENT)
				(*op)->type = OP_SUBSHELL;
			return (RETURN_OK);
		}
	}
	return (RETURN_FAIL);
}
