/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:57:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 13:55:36 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	set_xy(t_world *w)
{
	int		i;
	int		j;
	float	angle;

	angle = 30 * M_PI / 180;
	i = 0;
	while (i < w->height)
	{
		j = 0;
		while (j < w->width)
		{
			w->map[i][j].x = 50 + (j * 10 * cos(angle) - i * 10 * sin(angle));
			w->map[i][j].y = (i * 10 * cos(angle) + j * 10 * sin(angle)) -
								w->map[i][j].z * 1.5;
			j++;
		}
		i++;
	}
}

void	world_init(t_fdf *fdf)
{
	int		i;
	int		j;
	int		color = 255;

	set_xy(fdf->world);
	fdf->image = malloc(sizeof(t_image));
	fdf->image->width = fdf->world->width * 50;
	fdf->image->height = fdf->world->height * 50;
	fdf->image->image = mlx_new_image(fdf->mlx, fdf->image->width, fdf->image->height);
	fdf->image->data = mlx_get_data_addr(fdf->image->image, &fdf->image->bpp, &fdf->image->sl,
																&fdf->image->endian);
	printf("bpp: %d\nsl:  %d\nendian: %d\n", fdf->image->bpp, fdf->image->sl, fdf->image->endian);
	i = 0;
	while (i < fdf->world->height - 1)
	{
		j = 0;
		while (j < fdf->world->width - 1)
		{
			ft_printf("(%4d, %4d) ", fdf->world->map[i][j].x, fdf->world->map[i][j].y);
			draw_line_image(fdf->image, fdf->world->map[i][j], fdf->world->map[i][j + 1], color);
			draw_line_image(fdf->image, fdf->world->map[i][j], fdf->world->map[i + 1][j], color);
			//put_pixel_image(fdf->image, fdf->world->map[i][j].x, fdf->world->map[i][j].y, color);
			j++;
		}
		i++;
		ft_printf("\n");
	}
	fdf->image->x = 100;
	fdf->image->y = 100;
	mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, fdf->image->x, fdf->image->y);
}
