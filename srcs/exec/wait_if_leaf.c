/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_if_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:59:42 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/16 16:21:49 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_if_leaf(t_leaf_p leaf, int *rstatus)
{
	if (leaf)
		waitpid(leaf->pid, rstatus, 0);
}
