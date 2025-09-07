/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait_children.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/06 18:06:59 by cgajean           #+#    #+#             */
/*   Updated: 2025/09/07 14:21:06 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Je me pose la question d'ou waitpid les enfants, puisque des codes de retour des enfants depend l'execution d'une ligne (&&, ||, etc.)
// On ne peut pas waitpid a la fin comme c'est le cas actuellement, pour simplifier

// Il doit falloir wait entre chaque && et ||
// Avec une sequence d'extraction du code des qu'une fonction n'existe pas...

int	wait_children(t_minishell_p shell)
{
	int		cur_index;
	int		end_index;
	pid_t	*pid_table;
	int		*status_table;
	
	cur_index = 0;
	end_index = shell->exec_var.cur_index;
	pid_table = shell->exec_var.pid_table;
	status_table = shell->exec_var.status_table;
	while (cur_index < end_index)
	{
		waitpid(pid_table[cur_index], &status_table[cur_index], 0);
		cur_index++;
	}
	return (get_exit_code(shell));
}
