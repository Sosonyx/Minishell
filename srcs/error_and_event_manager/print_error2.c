/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_error2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 14:14:23 by ihadj             #+#    #+#             */
/*   Updated: 2025/10/14 14:14:36 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_generic_error2(t_shell_p shell, char **errmsg)
{
	(void)shell;
	speak2(NULL, STDERR_FILENO, errmsg);
}
