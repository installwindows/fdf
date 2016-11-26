/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   binary_tree.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/25 19:25:38 by varnaud           #+#    #+#             */
/*   Updated: 2016/11/25 19:28:59 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BINARY_TREE_H
# define BINARY_TREE_H

typedef struct		s_node
{
	void			*value;
	size_t			size;
	struct s_node	*left;
	struct s_node	*right;
}					t_node;

#endif

