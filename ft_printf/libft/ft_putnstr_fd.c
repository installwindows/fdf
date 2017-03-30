/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 19:38:48 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/21 19:40:36 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

int		ft_putnstr_fd(const char *str, size_t n, int fd)
{
	ssize_t	i;

	i = 0;
	while (*str && n)
	{
		i += ft_putchar_fd(*str, fd);
		str++;
		n--;
	}
	return (i);
}
