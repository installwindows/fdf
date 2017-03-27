/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:57:11 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 06:52:19 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	world_init(t_fdf *fdf)
{
	t_image	*image;
	int		i;
	int		j;
	int		color = 255;

	image = malloc(sizeof(t_image));
	image->width = 250;
	image->height = 250;
	image->image = mlx_new_image(fdf->mlx, image->width, image->height);
	image->data = mlx_get_data_addr(image->image, &image->bpp, &image->sl,
																&image->endian);
	printf("bpp: %d\nsl:  %d\nendian: %d\n", image->bpp, image->sl, image->endian);
	i = 0;
	j = 0;
	while (i < image->height)
	{
		j = 0;
		while (j < image->width)
		{
			put_pixel_image(image, j, i, color);
			if (j > image->width / 2)
				color = 0xe8739c;
			j++;
		}
		color = 255;
		i++;
	}
	mlx_put_image_to_window(fdf->mlx, fdf->window, image->image, 200, 200);
}
