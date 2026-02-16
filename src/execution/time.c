/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:17:05 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/16 14:36:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	get_time_ms(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec) * 1000
		+ (curr.tv_usec - anchor->tv_usec) / 1000);
}

long	get_time_us(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec) * 1000 * 1000
		+ (curr.tv_usec - anchor->tv_usec));
}

double	get_time_s(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec)
		+ (curr.tv_usec - anchor->tv_usec) / 1000.0 / 1000.0);
}


void	reset_render_time(t_gui *gui)
{
		gettimeofday(&gui->statistics.time_before_render, NULL);
}




