/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 15:23:27 by varnaud           #+#    #+#             */
/*   Updated: 2016/12/01 01:37:14 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "get_next_line.h"

static t_grid	*set_grid(char *file)
{
	int		fd;
	char	*line;
	t_grid	*grid;

	grid = malloc(sizeof(t_grid));
	grid->x = 0;
	grid->y = 0;
	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	while (get_next_line(fd, &line))
	{
		if (!grid->x)
			grid->x = ft_count_words(line, ' ');
		grid->y++;
		free(line);
	}
	grid->dots = malloc(sizeof(int*) * grid->y);
	grid->pos = malloc(sizeof(t_pos*) * grid->y);
	close(fd);
	return (grid);
}

static void		set_pos(t_grid *grid)
{
	int		i;
	int		j;
	int		x;
	int		y;
	float	angle;

	angle = 30 * M_PI / 180;
	i = 0;
	while (i < grid->y)
	{
		grid->pos[i] = malloc(sizeof(t_pos) * grid->x);
		j = 0;
		while (j < grid->x)
		{
			grid->pos[i][j].x = (float)INCREMENT * j;
			grid->pos[i][j].y = (float)INCREMENT * i;
			x = grid->pos[i][j].x;
			y = grid->pos[i][j].y;
			grid->pos[i][j].x = PADDING + (x * cos(angle) - y * sin(angle));
			grid->pos[i][j].y = PADDING + (y * cos(angle) + x * sin(angle)) -
								grid->dots[i][j] * 1.5;
			j++;
		}
		i++;
	}
}

static void		read_file(char *file, t_grid *grid)
{
	char	*line;
	char	**split;
	int		fd;
	int		i;
	int		j;

	i = 0;
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		grid->dots[i] = malloc(sizeof(int) * grid->x);
		split = ft_strsplit(line, ' ');
		j = 0;
		while (split[j])
		{
			grid->dots[i][j] = ft_atoi(split[j]);
			free(split[j]);
			j++;
		}
		free(split);
		free(line);
		i++;
	}
	close(fd);
}

static void		display_grid(t_grid *grid, void *mlx_ptr, void *mlx_window)
{
	int		i;
	int		j;
	t_pos	b;

	i = 0;
	while (i < grid->y)
	{
		j = 0;
		while (j < grid->x)
		{
			if (j + 1 < grid->x)
				b = grid->pos[i][j + 1];
			else
				b = grid->pos[i][j];
			draw_line(mlx_ptr, mlx_window, grid->pos[i][j], b);
			if (i + 1 < grid->y)
				b = grid->pos[i + 1][j];
			else
				b = grid->pos[i][j];
			draw_line(mlx_ptr, mlx_window, grid->pos[i][j], b);
			j++;
		}
		i++;
	}
}

int				main(int argc, char **argv)
{
	int		fd;
	t_grid	*grid;
	void	*mlx_ptr;
	void	*mlx_window;

	if (argc == 2)
	{
		grid = set_grid(argv[1]);
		read_file(argv[1], grid);
		if (grid == NULL)
			return (0);
		set_pos(grid);
		mlx_ptr = mlx_init();
		mlx_window = mlx_new_window(mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "FDF");
		display_grid(grid, mlx_ptr, mlx_window);
		mlx_loop(mlx_ptr);
	}
	return (0);
}
