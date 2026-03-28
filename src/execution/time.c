/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/13 15:17:05 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:12:27 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Returns milliseconds elapsed since the anchor; updates the anchor. */
int	get_time_ms(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec) * 1000
		+ (curr.tv_usec - anchor->tv_usec) / 1000);
}

/* Returns microseconds elapsed since the anchor; updates the anchor. */
long	get_time_us(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec) * 1000 * 1000
		+ (curr.tv_usec - anchor->tv_usec));
}

/* Returns seconds elapsed since the anchor; updates the anchor. */
double	get_time_s(struct timeval *anchor)
{
	struct timeval	curr;

	gettimeofday(&curr, NULL);
	return ((curr.tv_sec - anchor->tv_sec)
		+ (curr.tv_usec - anchor->tv_usec) / 1000.0 / 1000.0);
}

/* Resets the render-time anchor in the GUI to the current time. */
void	reset_render_time(t_gui *gui)
{
	gettimeofday(&gui->statistics.time_before_render, NULL);
}
