#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include "libft.h"
#include "get_next_line.h"

int		main(void)
{
	char	*line;
	char	**split;
	int		i;
	int		fd;

	fd = open("42.fdf", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		i = 0;
		split = ft_strsplit(line, ' ');
		while (split[i])
		{
			printf("%d: %d\n", i, ft_atoi(split[i]));
			free(split[i]);
			i++;
		}
		printf("-------------------------------------------------------------\n");
		free(split);
		free(line);
	}
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
	close(fd);
	fd = open("42.fdf", O_RDONLY);
	while (get_next_line(fd, &line))
	{
		i = 0;
		split = ft_strsplit(line, ' ');
		while (split[i])
		{
			printf("%d: %d\n", i, ft_atoi(split[i]));
			free(split[i]);
			i++;
		}
		printf("-------------------------------------------------------------\n");
		free(split);
		free(line);
	}
	close(fd);

}
