/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/22 18:28:15 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 18:28:58 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	free_world(t_world *world)
{
	int		i;

	i = 0;
	while (i < world->height)
		free(world->map[i++]);
	free(world->map);
	free(world);
}

void	print_world(t_world *world)
{
	int		i;
	int		j;

	i = 0;
	while (i < world->height)
	{
		j = 0;
		while (j < world->width)
		{
			ft_printf("%-3d ", world->map[i][j].z);
			j++;
		}
		ft_printf("\n");
		i++;
	}
	ft_printf("Width:%5d\nHeight:%5d\n", world->width, world->height);
}

static void	set_hook(t_fdf *fdf)
{
	mlx_expose_hook(fdf->window, expose_hook, fdf);
	mlx_hook(fdf->window, KeyPress, 0, key_press_hook, fdf);
	mlx_hook(fdf->window, KeyRelease, 0, key_release_hook, fdf);
	mlx_hook(fdf->window, DestroyNotify, 0, exit_fdf_hook, fdf);
	mlx_loop_hook(fdf->mlx, loop_hook, fdf);
	//mlx_mouse_hook(fdf->window, mouse_hook, fdf);
}

int			main(int argc, char **argv)
{
	t_fdf	*fdf;

	if (argc != 2)
	{
		ft_fprintf(2, "Usage: fdf map.fdf\n");
		return (1);
	}
	fdf = malloc(sizeof(t_fdf));
	ft_memset(&fdf->keys, 0, sizeof(t_keys));
	fdf->width = 1600;
	fdf->height = 1200;
	fdf->world = set_world(argv[1]);
	if (fdf->world == NULL)
	{
		ft_fprintf(2, "Can't set the world.");
		return (1);
	}
	fdf->mlx = mlx_init();
	fdf->window = mlx_new_window(fdf->mlx, fdf->width, fdf->height, "FDF");
	set_hook(fdf);
	world_init(fdf);
	mlx_loop(fdf->mlx);
}
