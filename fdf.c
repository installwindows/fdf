/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/29 15:23:27 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/23 18:46:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <math.h>
#include "libft.h"
#include "mlx.h"
#include "fdf.h"

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

int		**read_file(char *file)
{
	char	*line;
	char	**split;
	int		**grid;
	int		fd;
	int		x;
	int		y;
	int		n;
	int		tmpx;
	int		tmpy;

	x = 500;
	y = 20;
	tmpx = x;
	tmpy = y;
	grid = malloc(sizeof(int**));
	fd = open(file, O_RDONLY);
	while (get_next_line(fd, &line))
	{
		split = ft_strsplit(line, ' ');
		while (*split)
		{
			n = ft_atoi(*split);
			tmpx += 15;
			tmpy += -15 + n;
			
		}
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
		fd = open(*++argv, O_RDONLY);
		if (fd == -1)
			return (1);
		close(fd);
	}
	else
	{
		testing();
	}
	return (0);
}
