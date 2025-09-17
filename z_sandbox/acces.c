#include <unistd.h>

int	main(void)
{
	int	a = access("/usr/bin/ls", F_OK);

	return (0);
}
