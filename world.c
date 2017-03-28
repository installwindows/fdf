/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:57:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/28 12:57:46 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_xy(t_world *w, int ll)
{
	int		i;
	int		j;
	float	angle;
	int		minx;
	int		miny;

	minx = 0;
	miny = 0;
	angle = 30 * M_PI / 180;
	i = 0;
	while (i < w->height)
	{
		j = 0;
		while (j < w->width)
		{
			w->map[i][j].x = (j * ll * cos(angle) - i * ll * sin(angle));
			w->map[i][j].y = (i * ll * cos(angle) + j * ll * sin(angle)) -
								w->map[i][j].z * 1.5;
			if (w->map[i][j].x < minx)
				ft_printf("i, j: %d, %d : %d\n", i, j, minx = w->map[i][j].x);
			if (w->map[i][j].y < miny)
				ft_printf("i, j: %d, %d : %d z:%d\n", i, j, miny = w->map[i][j].y, w->map[i][j].z);
			j++;
		}
		i++;
	}
	i = 0;
	while (i < w->height)
	{
		j = 0;
		while (j < w->width)
		{
			w->map[i][j].x += -minx;
			w->map[i][j].y += -miny;
			j++;
		}
		i++;
	}
	ft_printf("minx: %d\n miny: %d\n", minx, miny);
}

void	world_init(t_fdf *fdf)
{
	int		i;
	int		j;
	int		color = 255;
	int		line_size;

	line_size = 10;
	set_xy(fdf->world, line_size);
	fdf->image = malloc(sizeof(t_image));
	fdf->image->width = fdf->world->width * line_size * 2;
	fdf->image->height = fdf->world->height * line_size * 2;
	fdf->image->image = mlx_new_image(fdf->mlx, fdf->image->width, fdf->image->height);
	fdf->image->data = mlx_get_data_addr(fdf->image->image, &fdf->image->bpp, &fdf->image->sl,
																&fdf->image->endian);
	ft_printf("w: %d\nh: %d\n", fdf->world->width, fdf->world->height);
	ft_printf("bpp: %d\nsl:  %d\nendian: %d\n", fdf->image->bpp, fdf->image->sl, fdf->image->endian);
	ft_printf("image width: %d\nimage height: %d\n", fdf->image->width, fdf->image->height);
	i = 0;
	while (i < fdf->world->height - 1)
	{
		j = 0;
		while (j < fdf->world->width - 1)
		{
			//ft_printf("(%4d, %4d - %#6x) ", fdf->world->map[i][j].x, fdf->world->map[i][j].y, fdf->world->map[i][j].color);
			if (fdf->world->map[i][j].z - fdf->world->map[i][j + 1].z)
				color = 0x91806d;
			else if (fdf->world->map[i][j].z)
				color = 0xffffff;
			else
				color = 0x50a848;
			draw_line_image(fdf->image, fdf->world->map[i][j], fdf->world->map[i][j + 1], color);
			if (fdf->world->map[i][j].z - fdf->world->map[i + 1][j].z)
				color = 0x91806d;
			else if (fdf->world->map[i][j].z)
				color = 0xffffff;
			else
				color = 0x50a848;
			draw_line_image(fdf->image, fdf->world->map[i][j], fdf->world->map[i + 1][j], color);
			//put_pixel_image(fdf->image, fdf->world->map[i][j].x, fdf->world->map[i][j].y, color);
			j++;
		}
		i++;
		//ft_printf("\n");
	}
	ft_printf("Done.\n");
	fdf->image->x = (fdf->width - fdf->world->map[fdf->world->width / 2][fdf->world->height / 2].x * 2) / 2;
	fdf->image->y = (fdf->height - fdf->world->map[fdf->world->width / 2][fdf->world->height / 2].y * 2) / 2;
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, fdf->image->x, fdf->image->y);
}
