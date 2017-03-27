/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 06:36:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 06:46:19 by varnaud          ###   ########.fr       */
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
