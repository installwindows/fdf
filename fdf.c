/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 15:23:27 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/25 20:40:59 by varnaud          ###   ########.fr       */
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
	Xincrement = dx / (float) steps;
	Yincrement = dy / (float) steps;
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

	grid = malloc(sizeof(grid));
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
	close(fd);
	return (grid);
}

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
	printf("after quick %d %d\n", grid->x, grid->y);
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		printf("line: |%s|\n", line);
		grid->dots[i] = malloc(sizeof(int) * grid->x);
		split = ft_strsplit(line, ' ');
		j = 0;
		while (split[j])
		{
			grid->dots[i][j] = ft_atoi(split[j]);
			free(split[j++]);
		}
		free(split);
		free(line);
		i++;
	}
	close(fd);
	printf("after read\n");
	return (grid);
}



void	display_grid(t_grid *grid)
{

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
	b.x = 169;
	b.y = 571;
	draw_line(mlx_ptr, mlx_window, a, b, 0x00FF00);
	mlx_loop(mlx_ptr);
}

int		main(int argc, char **argv)
{
	int		fd;

	if (argc == 2)
	{
		t_grid *grid = read_file(*++argv);
		int	i;
		int	j;
		for (i = 0; i < grid->y; i++)
		{
			for (j = 0; j < grid->x; j++)
				printf("%d ", grid->dots[i][j]);
			printf("\n");
		}
	}
	else
	{
		testing();
	}
	return (0);
}
