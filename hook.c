/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:46:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 18:31:26 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, t_fdf *fdf)
{
	ft_printf("%d\n", keycode);
	return (0);
}

int		expose_hook(t_fdf *fdf)
{
	return (0);
}

int		mouse_hook(int button, int x, int y, t_fdf *fdf)
{
	if (button == SCROLL_UP || button == SCROLL_DOWN || button == SCROLL_LEFT
			|| button == SCROLL_RIGHT)
		mlx_clear_window(fdf->mlx, fdf->window);
	if (button == SCROLL_UP)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x, fdf->image->y -= 10);
	if (button == SCROLL_DOWN)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x, fdf->image->y += 10);
	if (button == SCROLL_LEFT)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x -= 10, fdf->image->y);
	if (button == SCROLL_RIGHT)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x += 10, fdf->image->y);
	ft_printf("%d: (%3d,%3d)\n", button, x, y);
	return (0);
}

int		key_press_hook(int key, t_fdf *fdf)
{
	if (key == ESC)
		exit(0);
	if (key == UP)
		fdf->keys.up = 1;
	if (key == DOWN)
		fdf->keys.down = 1;
	if (key == LEFT)
		fdf->keys.left = 1;
	if (key == RIGHT)
		fdf->keys.right = 1;
	return (0);
}

int		key_release_hook(int key, t_fdf *fdf)
{
	if (key == UP)
		fdf->keys.up = 0;
	if (key == DOWN)
		fdf->keys.down = 0;
	if (key == LEFT)
		fdf->keys.left = 0;
	if (key == RIGHT)
		fdf->keys.right = 0;
	return (0);
}

int		loop_hook(t_fdf *fdf)
{
	if (fdf->keys.up || fdf->keys.down || fdf->keys.left || fdf->keys.right)
		mlx_clear_window(fdf->mlx, fdf->window);
	if (fdf->keys.up)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x, fdf->image->y -= 10);
	if (fdf->keys.down)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x, fdf->image->y += 10);
	if (fdf->keys.left)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x -= 10, fdf->image->y);
	if (fdf->keys.right)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image,
											fdf->image->x += 10, fdf->image->y);
	return (0);	
}

int		exit_fdf_hook(t_fdf *fdf)
{
	mlx_destroy_window(fdf->mlx, fdf->window);
	exit(0);
}
