/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/26 20:46:58 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 06:05:20 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int		key_hook(int keycode, void *param)
{
	if (keycode == 53 || keycode == 65307)
		exit(0);
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
