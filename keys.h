/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: varnaud <varnaud@student.42.us.org>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/27 13:41:09 by varnaud           #+#    #+#             */
/*   Updated: 2017/03/27 13:44:58 by varnaud          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef KEYS_H
# define KEYS_H
# ifdef __APPLE__
#  define ESC 53
#  define UP 126
#  define DOWN 125
#  define LEFT 123
#  define RIGHT 124
# elif __linux__
#  define ESC 65307
# endif

#endif
