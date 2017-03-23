/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:28:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/22 20:53:30 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"
#include "ft_printf.h"
#include "libft.h"
#include "fdf.h"
#include "mlx.h"

t_world	*validate_file(const char *file)
{
	int		fd;
	int		i;
	int		width;
	char	*line = NULL;
	t_world	*world;

	width = 1;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	world = malloc(sizeof(t_world));
	ft_memset(world, 0, sizeof(t_world));
	while (get_next_line(fd, &line))
	{
		i = 0;
		while (line[i])
		{
			if (line[i] == '\n' && line[i + 1] != '\0')
				return (NULL);
			if (!ft_strchr("0123456789 ", line[i]))
				return (NULL);
			if (line[i] == ' ')
			{
				while (line[i] == ' ')
					i++;
				width++;
				continue ;
			}
			i++;
		}
		if (!(world->width))
			world->width = width;
		if (world->width != width)
			return (NULL);
		world->height++;
		free(line);
	}
	close(fd);
	return (world);
}

int		set_map(const char *file, t_world *world)
{
	int		fd;
	int		i;
	int		j;
	char	*line = NULL;
	char	**split;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	world->map = malloc(sizeof(t_point*) * (world->height + 1));
	i = 0;
	while (get_next_line(fd, &line))
	{
		world->map[i] = malloc(sizeof(t_point) * (world->width + 1));
		split = ft_strsplit(line, ' ');
		j = 0;
		while (split[j])
		{
			world->map[i][j].z = ft_atoi(split[j]);
			free(split[j]);
			j++;
		}
		free(split);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

t_world	*set_world(const char *file)
{
	t_world	*world;

	world = validate_file(file);
	if (world == NULL)
		return (NULL);
	if (set_map(file, world))
		return (NULL);
	return (world);
}

void	free_world(t_world *world)
{
	int		i;

	i = 0;
	while (i < world->height)
		free(world->map[i]);
	free(world->map);
	free(world);
}

void	print_world(t_world *world)
{
	int		i;
	int		j;

	i = 0;
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			ft_printf("%-3d ", world->map[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

int		key_hook(int keycode, void *param)
{
	if (keycode == 53)
		exit(0);
	return (0);
	//ft_printf("%d\n", keycode);
}

int		main(int argc, char **argv)
{
	void	*mlx;
	void	*window;
	t_world	*world;

	if (argc == 2)
	{
		world = set_world(argv[1]);
		if (world == NULL)
		{
			perror("fdf");
			return (1);
		}
		print_world(world);
		exit(0);
		mlx = mlx_init();
		window = mlx_new_window(mlx, 800, 600, "FDF");
		mlx_key_hook(window, key_hook, NULL);
		mlx_loop(mlx);
	}
}
