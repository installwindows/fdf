/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:57:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 17:05:21 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	pad(t_world *w, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	while (i < w->height)
	{
		j = 0;
		while (j < w->width)
		{
			w->map[i][j].x += x;
			w->map[i][j].y += y;
			j++;
		}
		i++;
	}
}

static void	set_xy(t_world *w, int ll)
{
	int		i;
	int		j;
	int		minx;
	int		miny;

	minx = 0;
	miny = 0;
	i = 0;
	while (i < w->height)
	{
		j = 0;
		while (j < w->width)
		{
			w->map[i][j].x = (j * ll * cos(ANGLE) - i * ll * sin(ANGLE));
			w->map[i][j].y = (i * ll * cos(ANGLE) + j * ll * sin(ANGLE)) -
								w->map[i][j].z * 1.5;
			if (w->map[i][j].x < minx)
				minx = w->map[i][j].x;
			if (w->map[i][j].y < miny)
				miny = w->map[i][j].y;
			j++;
		}
		i++;
	}
	pad(w, -minx, -miny);
}

void		world_init(t_fdf *fdf)
{
	int		i;
	int		j;
	int		color = 255;
	int		line_size;

	line_size = 10;
	set_xy(fdf->world, line_size);
	fdf->image = set_image(fdf, line_size);
	fdf->image->x = (fdf->width -
		fdf->world->map[fdf->world->width / 2][fdf->world->height / 2].x * 2)
		/ 2;
	fdf->image->y = (fdf->height - 
		fdf->world->map[fdf->world->width / 2][fdf->world->height / 2].y * 2)
		/ 2;
	mlx_put_image_to_window(fdf->mlx, fdf->window,
							fdf->image->image, fdf->image->x, fdf->image->y);
}
