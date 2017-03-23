/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 12:41:36 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/05 04:24:25 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1

typedef struct	s_fd
{
	int			fd;
	char		buf[BUFF_SIZE + 1];
	int			bytes_read;
	char		*line;
	int			eof;
}				t_fd;

int				get_next_line(const int fd, char **line);

#endif
