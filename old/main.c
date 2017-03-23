#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int		main(int argc, char **argv)
{
	int		fd;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		printf("fd: %d\n", fd);
		close(fd);
		fd = open(argv[1], O_RDONLY);
		printf("fd: %d\n", fd);
		close(fd);
	}
}
