/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:28:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/28 10:26:38 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

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
	while (gnl(fd, &line))
	{
		i = 0;
		width = 1;
		while (line[i])
		{
			if (!ft_strchr("0123456789,xXaAbBcCdDeEfF ", line[i]))
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
	while (gnl(fd, &line))
	{
		world->map[i] = malloc(sizeof(t_point) * (world->width + 1));
		split = ft_strsplit(line, ' ');
		j = 0;
		while (split[j])
		{
			world->map[i][j].z = ft_atoi(split[j]);
			world->map[i][j].color = -1;
			if (ft_strchr(split[j], ','))
				world->map[i][j].color = ft_atoi_base(ft_strchr(split[j], ',') + 3, 16);
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
		free(world->map[i++]);
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

int		main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc == 2)
	{
		fdf = malloc(sizeof(t_fdf));
		fdf->width = 1600;
		fdf->height = 1200;
		fdf->world = set_world(argv[1]);
		if (fdf->world == NULL)
		{
			perror("Can't set the world.");
			return (1);
		}
		//print_world(fdf->world);
		//free_world(fdf->world);
		//free(fdf);
		//exit(0);
		fdf->mlx = mlx_init();
		fdf->window = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FDF");
		mlx_key_hook(fdf->window, key_hook, fdf);
		mlx_expose_hook(fdf->window, expose_hook, fdf);
		mlx_mouse_hook(fdf->window, mouse_hook, fdf);
		world_init(fdf);
		mlx_loop(fdf->mlx);
	}
}
