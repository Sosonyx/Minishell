/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_if_leaf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cgajean <cgajean@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:59:42 by cgajean           #+#    #+#             */
/*   Updated: 2025/10/06 12:22:55 by cgajean          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	wait_if_leaf(t_leaf_p leaf, int *rstatus)
{
	if (leaf && leaf->pid)
		waitpid(leaf->pid, rstatus, 0);
}
