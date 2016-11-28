/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 15:23:27 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/27 17:02:02 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "fdf.h"
#include "get_next_line.h"

void	draw_line(void *mlx_ptr, void *mlx_window, t_pos a, t_pos b, int color)
{
	int		dx;
	int		dy;
	int		steps;
	float	Xincrement;
	float	Yincrement;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
	else
		steps = ft_abs(dy);
	Xincrement = (float) dx / (float) steps;
	Yincrement = (float) dy / (float) steps;
	while (steps--)
	{
		a.x += Xincrement;
		a.y += Yincrement;
		mlx_pixel_put(mlx_ptr, mlx_window, round(a.x), round(a.y), color);
	}
}
t_grid	*quick_and_dirty(char *file)
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
	if (grid->dots == NULL)
	{
		printf("grid->dots is NULL\n");
		return (NULL);
	}
	close(fd);
	return (grid);
}

void	set_pos(t_grid *grid)
{
	int		i;
	int		j;

	grid->pos = malloc(sizeof(t_pos*) * grid->y);
	i = 0;
	while (i < grid->y)
	{
		grid->pos[i] = malloc(sizeof(t_pos) * grid->x);
		j = 0;
		while (j < grid->x)
		{
			grid->pos[i][j].x = (float)INCREMENT * j;
			grid->pos[i][j].y = (float)INCREMENT * i;
			int x = grid->pos[i][j].x;
			int y = grid->pos[i][j].y;
			float angle = 30*M_PI/180;

			grid->pos[i][j].x = PADDING + (x * cos(angle) - y * sin(angle));
			grid->pos[i][j].y = PADDING + (y * cos(angle) + x * sin(angle)) - grid->dots[i][j] * 1.5;
			j++;
		}
		i++;
	}
}

/*
t_node	*read_file_node(int fd)
{
	char	*line;
	char	**split;
	t_node	*head;
	t_node	*current;
	t_node	*previous;

	previous = NULL;
	head = NULL;
	current = head;
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, ' ');
		while (*split)
		{
			current = malloc(sizeof(t_node));
			set_content(current, ft_atoi(*split));
			free(*split);
			split++;
			if (previous)
			{
				previous->left = current;

			}
			current = current->right;
		}

	}
}
*/
t_grid	*read_file(char *file)
{
	char	*line;
	char	**split;
	int		fd;
	int		i;
	int		j;
	t_grid	*grid;

	i = 0;
	grid = quick_and_dirty(file);
	if (grid == NULL)
	{
		printf("quick_and_dirty failed\n");
		return (NULL);
	}
	printf("after quick %d %d\n", grid->x, grid->y);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("line: |%s|\n", line);
		grid->dots[i] = malloc(sizeof(int) * grid->x);
		if (grid->dots[i] == NULL)
		{
			printf("grid->dots[%d] is NULL\n", i);
			return (NULL);
		}
		split = ft_strsplit(line, ' ');
		j = 0;
		while (split[j])
		{
			grid->dots[i][j] = ft_atoi(split[j]);
			//free(split[j]);
			j++;
		}
		//free(split);
		free(line);
		i++;
	}
	close(fd);
	printf("after read\n");
	return (grid);
}

void	display_grid(t_grid *grid, void *mlx_ptr, void *mlx_window)
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
			printf("(%d, %d) ", i, j);
			if (j + 1 < grid->x)
				b = grid->pos[i][j + 1];
			else
				b = grid->pos[i][j];
			draw_line(mlx_ptr, mlx_window, grid->pos[i][j], b, 0xFFFFFF);
			if (i + 1 < grid->y)
				b = grid->pos[i + 1][j];
			else
				b = grid->pos[i][j];
			draw_line(mlx_ptr, mlx_window, grid->pos[i][j], b, 0xFFFFFF);
			j++;
		}
		i++;
	}
}

void	testing(void)
{
	void	*mlx_ptr;
	void	*mlx_window;
	t_pos	a;
	t_pos	b;

	a.x = 5;
	a.y = 5;
	b.x = 40;
	b.y = 40;

	mlx_ptr = mlx_init();
	mlx_window = mlx_new_window(mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "Ayy");
	draw_line(mlx_ptr, mlx_window, a, b, 0xFF0000);
	a.x = 80;
	a.y = 80;
	b.x = 160;
	b.y = 100;
	draw_line(mlx_ptr, mlx_window, a, b, 0x00FF00);
	a.x = 200;
	a.y = 200;
	b.x = 200;
	b.y = 200;
	draw_line(mlx_ptr, mlx_window, a, b, 0x0000FF);
	mlx_loop(mlx_ptr);
}

int		main(int argc, char **argv)
{
	int		fd;

	if (argc == 2)
	{
		t_grid *grid = read_file(*++argv);
		if (grid == NULL)
		{
			printf("main grid is NULL\n");
			return (0);
		}
		int	i;
		int	j;
		for (i = 0; i < grid->y; i++)
		{
			for (j = 0; j < grid->x; j++)
				printf("%d ", grid->dots[i][j]);
			printf("\n");
		}
		set_pos(grid);
		for (i = 0; i < grid->y; i++)
		{
			printf("%d:\n", i);
			for (j = 0; j < grid->x; j++)
				printf("j:%d(%.0f,%.0f)  ", j, grid->pos[i][j].x, grid->pos[i][j].y);
			printf("\n\n");
		}
		printf("ALLL DONDEEE\n");
		void *mlx_ptr = mlx_init();
		void *mlx_window = mlx_new_window(mlx_ptr, WIN_HEIGHT, WIN_WIDTH, "Ayy");
		display_grid(grid, mlx_ptr, mlx_window);
		mlx_loop(mlx_ptr);
	}
	else
	{
		testing();
	}
	return (0);
}
