/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 01:27:55 by varnaud           #+#    #+#             */
/*   Updated: 2016/12/01 01:31:50 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "mlx.h"
#include "libft.h"
#include "fdf.h"

void	draw_line(void *mlx_ptr, void *mlx_window, t_pos a, t_pos b)
{
	int		dx;
	int		dy;
	int		steps;
	float	xincrement;
	float	yincrement;

	dx = b.x - a.x;
	dy = b.y - a.y;
	if (ft_abs(dx) > ft_abs(dy))
		steps = ft_abs(dx);
	else
		steps = ft_abs(dy);
	xincrement = (float)dx / (float)steps;
	yincrement = (float)dy / (float)steps;
	while (steps--)
	{
		a.x += xincrement;
		a.y += yincrement;
		mlx_pixel_put(mlx_ptr, mlx_window, round(a.x), round(a.y), 0xFFFFFF);
	}
}
