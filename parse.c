/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:18:56 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/30 00:15:54 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static int		trim(char *line)
{
	int		i;

	i = 0;
	while (line [i] && line[i] == ' ')
		i++;
	return (i);
}

static t_world	*get_dimension(const char *file, char *line)
{
	int		fd;
	int		i;
	t_world	*world;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (NULL);
	world = malloc(sizeof(t_world));
	ft_memset(world, 0, sizeof(t_world));
	while ((i = gnl(fd, &line)) != -1 && i)
	{
		if (!world->width && !(i = 0))
			while (1)
			{
				while (line[i] == ' ')
					i++;
				if (!line[i])
					break ;
				while (line[i] && line[i] != ' ')
					i++;
				world->width++;
			}
		world->height += ft_strchr("-0123456789", line[trim(line)]) ? 1 : 0;
		free(line);
	}
	close(fd);
	return (world);
}

static int		set_line(t_point *p, char *line, t_world *w)
{
	char	**split;
	int		j;

	split = ft_strsplit(line, ' ');
	j = 0;
	while (split[j] && j < w->width)
	{
		p[j].z = ft_atoi(split[j]);
		p[j].color = -1;
		if (ft_strchr(split[j], ','))
			p[j].color = ft_atoi_base(ft_strchr(split[j], ',') + 3, 16);
		free(split[j]);
		j++;
	}
	if (j != w->width)
		return (1);
	while (split[j])
		free(split[j++]);
	free(split);
	return (0);
}

static int		set_map(const char *file, t_world *world)
{
	int		fd;
	int		i;
	char	*line;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	world->map = malloc(sizeof(t_point*) * (world->height + 1));
	i = 0;
	while (gnl(fd, &line) && i < world->height)
	{
		world->map[i] = malloc(sizeof(t_point) * (world->width + 1));
		if (set_line(world->map[i], line, world))
			return (1);
		free(line);
		i++;
	}
	if (i != world->height)
		return (1);
	close(fd);
	return (0);
}

t_world			*set_world(const char *file)
{
	t_world	*world;

	world = get_dimension(file, NULL);
	if (world == NULL)
		return (NULL);
	if (world->width <= 0 || world->height <= 0)
		return (NULL);
	if (set_map(file, world))
		return (NULL);
	return (world);
}
