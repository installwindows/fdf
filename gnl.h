/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/23 23:43:03 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/24 00:22:50 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GNL_H
# define GNL_H
# define BUFF_SIZE 1024

typedef struct	s_fd
{
	int			fd;
	int			i;
	int			size;
	char		*buf;
	struct s_fd	*next;
}				t_fd;

int				gnl(const int fd, char **line);

t_fd			*get_or_rm_fd(t_fd **l, int fd, int del);
t_fd			*add_fd(t_fd **list, int fd);

#endif
