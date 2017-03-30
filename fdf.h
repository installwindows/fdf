/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:34:06 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 18:28:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include <X11/X.h>
# include "gnl.h"
# include "ft_printf.h"
# include "libft.h"
# include "mlx.h"
# include "keys.h"
# define ANGLE 30.0 * M_PI / 180.0

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

typedef struct	s_keys
{
	int			up;
	int			down;
	int			left;
	int			right;
}				t_keys;


typedef struct	s_fdf
{
	void		*mlx;
	void		*window;
	int			width;
	int			height;
	t_world		*world;
	t_image		*image;
	t_keys		keys;
}				t_fdf;

t_world			*set_world(const char *file);
t_image			*set_image(t_fdf *fdf, int ls);
void			world_init(t_fdf *fdf);
int				key_hook(int keycode, t_fdf *fdf);
int				expose_hook(t_fdf *fdf);
int				mouse_hook(int button, int x, int y, t_fdf *fdf);


int				key_press_hook(int key, t_fdf *fdf);
int				key_release_hook(int key, t_fdf *fdf);
int				loop_hook(t_fdf *fdf);
int				exit_fdf_hook(t_fdf *fdf);

int				put_pixel_image(t_image *img, int x, int y, int color);
int				dw_line(t_image *img, t_point a, t_point b, int color);

#endif
