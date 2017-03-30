/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 16:45:43 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 17:06:00 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	set_color(int a, int b, int *color)
{
	if (a - b)
		*color = 0x91806d;
	else if (a)
		*color = 0xffffff;
	else
		*color = 0x50a848;
}

t_image		*set_image(t_fdf *fdf, int ls)
{
	int		i;
	int		j;
	int		c;
	t_image	*image;

	image = malloc(sizeof(t_image));
	image->width = fdf->world->width * ls * 2;
	image->height = fdf->world->height * ls * 2;
	image->image = mlx_new_image(fdf->mlx, image->width, image->height);
	image->data = mlx_get_data_addr(image->image, &image->bpp, &image->sl,
																&image->endian);
	i = 0;
	while (i < fdf->world->height - 1)
	{
		j = 0;
		while (j < fdf->world->width - 1)
		{
			set_color(fdf->world->map[i][j].z, fdf->world->map[i][j + 1].z, &c);
			dw_line(image, fdf->world->map[i][j], fdf->world->map[i][j + 1], c);
			set_color(fdf->world->map[i][j].z, fdf->world->map[i + 1][j].z, &c);
			dw_line(image, fdf->world->map[i][j], fdf->world->map[i + 1][j], c);
			j++;
		}
		i++;
	}
	return (image);
}
