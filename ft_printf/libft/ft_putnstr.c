/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/30 16:05:33 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/19 15:09:20 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

ssize_t	ft_putnstr(const char *str, size_t n)
{
	ssize_t	i;

	i = 0;
	while (*str && n)
	{
		i += ft_putchar(*str);
		str++;
		n--;
	}
	return (i);
}
