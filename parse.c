/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/29 15:18:56 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/29 16:05:22 by varnaud          ###   ########.fr       */
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
	ft_memset(world, (i = 0), sizeof(t_world));
	while (gnl(fd, &line))
	{
		if (!world->width)
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
		world->height += ft_strchr("0123456789", line[trim(line)]) ? 1 : 0;
		free(line);
	}
	close(fd);
	return (world);
}

static void		set_line(t_point *p, char *line)
{
	char	**split;
	int		j;

	split = ft_strsplit(line, ' ');
	j = 0;
	while (split[j])
	{
		p[j].z = ft_atoi(split[j]);
		p[j].color = -1;
		if (ft_strchr(split[j], ','))
			p[j].color = ft_atoi_base(ft_strchr(split[j], ',') + 3, 16);
		free(split[j]);
		j++;
	}
	free(split);
}

static int		set_map(const char *file, t_world *world)
{
	int		fd;
	int		i;
	int		j;
	char	*line;
	char	**split;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (1);
	world->map = malloc(sizeof(t_point*) * (world->height + 1));
	i = 0;
	while (gnl(fd, &line))
	{
		world->map[i] = malloc(sizeof(t_point) * (world->width + 1));
		set_line(world->map[i], line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

t_world			*set_world(const char *file)
{
	t_world	*world;

	world = get_dimension(file, NULL);
	if (world == NULL)
		return (NULL);
	if (set_map(file, world))
		return (NULL);
	return (world);
}
