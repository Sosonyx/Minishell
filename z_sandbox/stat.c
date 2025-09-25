#define _GNU_SOURCE
#include <sys/stat.h>
#include <stdio.h>


int	main(void)
{
	struct stat	st;
	char		*name[] = {"minishell", "srcs", "to_do_list"};

	for (int i = 0; i < 3; i++)
	{
		printf("%d\n", stat(name[i], &st));
		printf("%d\n", lstat(name[i], &st));
	}

	return (0);
}
