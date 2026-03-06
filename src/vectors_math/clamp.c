/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/06 16:07:37 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/06 16:18:00 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// clamp value to interval 
double clamp(double value, t_interval interval)
{
	return fmax(interval.min, fmin(interval.max, value));
}

// clamp value to interval 
void clamp_p(double *value, t_interval interval)
{
	*value = fmax(interval.min, fmin(interval.max, *value));
}

t_vec3 clamp_vec3(t_vec3 value, t_interval interval)
{
	value.x = clamp(value.x, interval);
	value.y = clamp(value.y, interval);
	value.z = clamp(value.z, interval);
	return (value);
}

void clamp_vec3_p(t_vec3 *value, t_interval interval)
{
	clamp_p(&value->x, interval);
	clamp_p(&value->y, interval);
	clamp_p(&value->z, interval);
}
