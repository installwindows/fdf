/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/26 19:16:44 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/27 22:32:42 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <math.h>
#include "libft.h"
#include "ftl.h"

t_fdf	*read_file(int fd)
{
	char	buf[1];
	int		n;
	int		i;
	int		new_n;
	t_fdf	*fdf;
	t_p		*c;
	t_p		*p;
	t_p		*u;
	t_p		*f;
	t_p		*t;

	fdf = malloc(sizeof(fdf));
	c = NULL;
	p = NULL;
	f = NULL;
	u = NULL;
	fdf->p = c;
	n = 0;
	i = 0;
	new_n = 0;
	while (read(fd, buf, 1))
	{
		if (ft_isdigit(buf[0]))
		{
			n = n * 10 + (buf[0] - '0');
			printf("%d", n);
			new_n = 1;
		}
		else
		{
			if (new_n)
			{
				c = malloc(sizeof(t_p));
				if (fdf->p == NULL)
					fdf->p = c;
				if (!f)
					f = c;
				c->z = n;
				c->right = NULL;
				c->left = NULL;
				if (p)
					p->right = c;
				p = c;
				n = 0;
				new_n = 0;
			}
		}
		if (*buf == '\n')
		{
			printf("new line\n");
			t = f;
			while (u && t)
			{
				u->left = t;
				printf("u: %d && f ", u->z);
				u = u->right;
				t = t->right;
			}
			u = f;
			f = NULL;
			p = NULL;
			i++;
		}
	}
	return (fdf);
}

void	display_tree(t_p *p)
{
	if (p->right)
		display_tree(p->right);
	printf("%2d ", p->z);
	if (p->left)
		display_tree(p->left);
}

int		main(int argc, char **argv)
{
	int		fd;
	t_fdf	*fdf;

	if (argc == 2)
	{
		if ((fd = open(*++argv, O_RDONLY)) == -1)
			return (0);
		fdf = read_file(fd);
		close(fd);
		printf("fdf\n");
		display_tree(fdf->p);
	}
}
