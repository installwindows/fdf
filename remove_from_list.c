/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_from_list.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/23 23:52:48 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/24 00:44:03 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "get_next_line.h"
#include "libft.h"

static void	free_fd(t_fd *f)
{
	if (f->file != NULL)
		free(f->file);
	free(f);
}

void		remove_from_list(t_list **list, int fd)
{
	t_list	*current;
	t_list	*previous;

	current = *list;
	previous = *list;
	while (current)
	{
		if (((t_fd*)(current->content))->fd == fd)
		{
			free_fd((t_fd*)(current->content));
			previous->next = current->next;
			free(current);
			break ;
		}
		previous = current;
		current = current->next;
	}
}
