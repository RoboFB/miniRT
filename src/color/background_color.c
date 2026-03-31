/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   background_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/31 11:44:23 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/31 11:45:25 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Returns a sky-gradient background color based on ray direction. */
t_vec3	background_color_nice(const t_ray *ray)
{
	t_vec3	color;
	t_vec3	norm_direction;
	double	a;

	norm_direction = normalize_vec3(ray->direction);
	a = 0.5 * (norm_direction.y + 1.0);
	color.x = (1.0 - a) * 1.0 + (a * 0.5);
	color.y = (1.0 - a) * 1.0 + (a * 0.7);
	color.z = (1.0 - a) * 1.0 + (a * 1.0);
	return (color);
}

t_vec3	background_color_subject(void)
{
	return ((t_vec3){0});
}
