/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 20:11:53 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/23 23:52:39 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>
#include "libft.h"
#include "get_next_line.h"

static int	cmp_fd(const void *elem, const void *fd)
{
	const t_fd	*celem;
	const int	*cfd;

	celem = elem;
	cfd = fd;
	return (celem->fd == *cfd);
}

static int	read_file(t_fd *f, int fd)
{
	char	buf[BUFF_SIZE];
	int		bytes_read;

	f->isdone = 0;
	f->line = NULL;
	f->fd = fd;
	f->size = 0;
	f->file = NULL;
	f->isbinary = 0;
	while ((bytes_read = read(f->fd, buf, BUFF_SIZE)))
	{
		if (bytes_read == -1)
			return (-1);
		if (!f->isbinary)
			f->isbinary = ft_memchr(buf, 0x00, bytes_read) == NULL ? 0 : 1;
		ft_memadd((void**)&(f->file), buf, f->size, bytes_read);
		f->size += bytes_read;
	}
	f->isread = 1;
	return (1);
}

static char	*read_binary(t_fd *f)
{
	char	*tmp;
	int		size;

	size = f->size - BUFF_SIZE >= 0 ? BUFF_SIZE : f->size;
	if (f->size == size)
		f->isdone = 1;
	f->line = (char*)malloc(size * sizeof(char));
	ft_memcpy(f->line, f->file, size);
	tmp = (char*)malloc((f->size - size) * sizeof(char));
	ft_memcpy(tmp, f->file + size, f->size - size);
	f->size -= size;
	free(f->file);
	f->file = tmp;
	f->bytes_read = size;
	return (f->line);
}

static char	*read_line(t_fd *f)
{
	char	*t;
	int		size;

	t = ft_memchr(f->file, '\n', f->size);
	if (t != NULL && f->size == t - f->file + 1)
	{
		f->isdone = 1;
		size = f->size - 1;
	}
	else if (t == NULL)
	{
		f->isdone = 1;
		size = f->size;
	}
	else
		size = t - f->file;
	f->line = (char*)malloc((size + 1) * sizeof(char));
	ft_memcpy(f->line, f->file, size);
	f->line[size] = '\0';
	t = ft_memalloc(f->size - size);
	ft_memcpy(t, f->file + size + 1, f->size - size);
	f->size -= (size + 1);
	free(f->file);
	f->file = t;
	return (f->line);
}

int			get_next_line(const int fd, char **line)
{
	static t_list	*list;
	t_list			*current;
	t_fd			*f;

	if (line == NULL || fd < 0)
		return (-1);
	if ((current = ft_lstget(list, &fd, cmp_fd)) == NULL)
	{
		f = (t_fd*)malloc(sizeof(t_fd));
		f->isread = 0;
		ft_lstadd(&list, (current = ft_lstnew(f, sizeof(t_fd))));
		free(f);
	}
	f = current->content;
	if (!(f->isread) && read_file(f, fd) == -1)
		return (-1);
	if (f->isdone)
	{
		remove_from_list(&list, fd);
		return (0);
	}
	*line = f->isbinary ? read_binary(f) : read_line(f);
	return (f->isbinary ? f->bytes_read : 1);
}
