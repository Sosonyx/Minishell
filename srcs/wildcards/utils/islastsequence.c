/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   islastsequence.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fox <fox@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/23 16:02:19 by fox               #+#    #+#             */
/*   Updated: 2025/09/23 16:02:31 by fox              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wildcards.h"

bool	islastsequence(char *field)
{
	while (*field && isasterisk(*field))
		field++;
	while (*field)
		if (isasterisk(*field++))
			return (0);
	return (1);
}
