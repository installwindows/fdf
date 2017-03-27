/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:46:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 13:52:51 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, void *param)
{
	t_fdf	*fdf;

	fdf = param;
	if (keycode == 53 || keycode == 65307)
		exit(0);
	else if (keycode == UP)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, fdf->image->x, fdf->image->y -= 10);
	else if (keycode == DOWN)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, fdf->image->x, fdf->image->y += 10);
	else if (keycode == LEFT)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, fdf->image->x -= 10, fdf->image->y);
	else if (keycode == RIGHT)
		mlx_put_image_to_window(fdf->mlx, fdf->window, fdf->image->image, fdf->image->x += 10, fdf->image->y);


ft_printf("%d\n", keycode);
	return (0);
}

int		expose_hook(void *param)
{
	ft_printf("Expose hook\n");
	return (0);
}

int		mouse_hook(int button, int x, int y, void *param)
{
	ft_printf("%d: (%3d,%3d)\n", button, x, y);
	return (0);
}
