/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/27 17:06:37 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/27 20:29:14 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_p
{
	int			x;
	int			y;
	int			z;
	struct s_p	*right;
	struct s_p	*left;
}				t_p;

typedef struct	s_fdf
{
	int		height;
	int		width;
	int		line_length;
	t_p		*p;
}				t_fdf;
