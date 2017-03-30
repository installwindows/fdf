/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 06:36:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 17:06:48 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		put_pixel_image(t_image *img, int x, int y, int color)
{
	if (x < 0 || y < 0 || x >= img->width || y >= img->height)
		return (-1);
	ft_memcpy(img->data + x * (img->bpp / 8) + y * img->sl, &color,
																(img->bpp / 8));
	return (0);
}

int		dw_line(t_image *img, t_point a, t_point b, int color)
{
	int		steps;
	float	xi;
	float	yi;
	float	x;
	float	y;

	steps = ft_abs(b.x - a.x) > ft_abs(b.y - a.y) ? ft_abs(b.x - a.x) :
															ft_abs(b.y - a.y);
	xi = (float)(b.x - a.x) / (float)steps;
	yi = (float)(b.y - a.y) / (float)steps;
	x = a.x;
	y = a.y;
	while (steps--)
	{
		x += xi;
		y += yi;
		put_pixel_image(img, round(x), round(y), color);
	}
	return (0);
}
