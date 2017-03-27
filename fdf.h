/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:34:06 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 06:43:42 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "gnl.h"
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"

typedef struct	s_point
{
	int			x;
	int			y;
	int			z;
}				t_point;

typedef struct	s_world
{
	t_point		**map;
	int			width;
	int			height;
}				t_world;

typedef struct	s_fdf
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_world		*world;
}				t_fdf;

typedef struct	s_image
{
	int			width;
	int			height;
	void		*image;
	char		*data;
	int			bpp;
	int			sl;
	int			endian;
}				t_image;

void			world_init(t_fdf *fdf);
int				key_hook(int keycode, void *param);
int				expose_hook(void *param);
int				mouse_hook(int button, int x, int y, void *param);

int				put_pixel_image(t_image *img, int x, int y, int color);

#endif
