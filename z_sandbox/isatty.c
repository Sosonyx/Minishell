/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isatty.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihadj <ihadj@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/04 14:01:36 by ihadj             #+#    #+#             */
/*   Updated: 2025/09/04 14:01:36 by ihadj            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE

#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int	main(void)
{
	int	fd = open("./getenv.c", O_RDONLY);

	printf("Slot -> %d\n", ttyslot());

	printf("\nSTDIN_FILENO is tty: %s -> name: %s", isatty(STDIN_FILENO) == 1 ? "yes" : "no", ttyname(STDIN_FILENO));
	printf("\nSTDOUT_FILENO is tty: %s -> name: %s", isatty(STDOUT_FILENO) == 1 ? "yes" : "no", ttyname(STDOUT_FILENO));
	printf("\nSTDERR_FILENO is tty: %s -> name: %s", isatty(STDERR_FILENO) == 1 ? "yes" : "no", ttyname(STDERR_FILENO));
	printf("\nRegular fd is tty: %s -> name: %s", isatty(fd) == 1 ? "yes" : "no", ttyname(fd));

	dup2(fd, STDIN_FILENO);
	printf("\nSTDIN_FILENO dupped is tty: %s -> name: %s", isatty(STDIN_FILENO) == 1 ? "yes" : "no", ttyname(STDIN_FILENO));
	printf("\n\n");

	close(fd);
	return (0);
}

