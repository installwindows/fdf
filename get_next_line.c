/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 12:42:51 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/22 20:55:23 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	contain_new_line(const char *s, size_t size)
{
	size_t	i;

	i = 0;
	if (s == NULL)
		return (-1);
	while (i < size)
	{
		if (s[i] == '\n' || s[i] == EOF)
			return (i);
		i++;
	}
	return (-1);
}

static int	cmp_fd(const void *elem, const void *fd)
{
	const t_fd	*celem;
	const int	*cfd;

	celem = elem;
	cfd = fd;
	return (celem->fd == *cfd);
}

static t_fd	*new_fd(int fd)
{
	t_fd	*new;

	new = (t_fd*)malloc(sizeof(t_fd));
	new->fd = fd;
	ft_memset(new->buf, 0, BUFF_SIZE + 1);
	new->bytes_read = 0;
	new->line = NULL;
	new->eof = 0;
	return (new);
}

static int	read_buf(t_fd *f, char **line)
{
	int		i;
	size_t	size;

	size = 0;
	while ((i = contain_new_line(f->buf, (size_t)f->bytes_read)) == -1)
	{
		ft_memadd((void**)&(f->line), f->buf, size, f->bytes_read + 1);
		size += f->bytes_read;
		if ((f->bytes_read = read(f->fd, f->buf, BUFF_SIZE)) == -1)
			return (-1);
		if (f->bytes_read == 0 && ((*line = f->line) || 1))
			return (f->eof = 1);
		f->buf[f->bytes_read] = '\0';
	}
	ft_memadd((void**)&(f->line), f->buf, size, i);
	if (i == 0 && size == 0)
		f->line = ft_strnew(0);
	if (f->line != NULL)
		f->line[size + i] = '\0';
	ft_memcpy(f->buf, f->buf + i + 1, f->bytes_read - i - 1);
	f->bytes_read = f->bytes_read - i - 1;
	f->buf[f->bytes_read] = '\0';
	*line = f->line;
	return (1);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*fds;
	t_list			*current;
	t_fd			*f;

	if (line == NULL)
		return (-1);
	current = ft_lstget(fds, &fd, cmp_fd);
	if (current == NULL)
	{
		current = ft_lstnew(new_fd(fd), sizeof(t_fd));
		ft_lstadd(&fds, current);
	}
	f = current->content;
	//if (f->line != NULL)
	//{
	//	free(f->line);
	//	f->line = NULL;
	//}
	return (f->eof ? 0 : read_buf(f, line));
}
