/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_is_root.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sosony <sosony@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 16:45:53 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/15 20:30:05 by sosony           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_is_root(t_shell_p shell, t_ast_p *ast)
{
	if (!shell->is_root)
	{
		shell->ast_root = *ast;
		shell->is_root = true;
	}
}
