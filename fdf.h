/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:34:06 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/28 10:16:15 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "gnl.h"
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include "keys.h"

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
	int			color;
}				t_point;

typedef struct	s_world
{
	t_point		**map;
	int			width;
	int			height;
}				t_world;

typedef struct	s_image
{
	int			width;
	int			height;
	void		*image;
	char		*data;
	int			bpp;
	int			sl;
	int			endian;
	int			x;
	int			y;
}				t_image;

typedef struct	s_fdf
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_world		*world;
	t_image		*image;
}				t_fdf;

void			world_init(t_fdf *fdf);
int				key_hook(int keycode, void *param);
int				expose_hook(void *param);
int				mouse_hook(int button, int x, int y, void *param);

int				put_pixel_image(t_image *img, int x, int y, int color);
int				draw_line_image(t_image *img, t_point a, t_point b, int color);

#endif
