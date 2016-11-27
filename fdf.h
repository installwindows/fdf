/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/22 22:11:15 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/26 20:35:47 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# define WIN_HEIGHT 750
# define WIN_WIDTH 750
# define PADDING 250
# define INCREMENT 20

typedef struct	s_pos
{
	float		x;
	float		y;
	int			z;
}				t_pos;

typedef struct	s_grid
{
	t_pos		**pos;
	int			**dots;
	int			x;
	int			y;
}				t_grid;

#endif

