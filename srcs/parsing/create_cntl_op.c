/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_cntl_op.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/29 12:34:24 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/29 17:38:02 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_cntl_op(t_minishell_p shell, t_ast_p *op, t_toktype type)
{
	*op = ft_calloc(1, sizeof(t_ast));
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
	else
	{
		set_abort(shell, MEM_ERRMSG);
		return (RETURN_FAIL);
	}
}
