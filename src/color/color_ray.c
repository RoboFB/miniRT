/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/02 11:11:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// aka ray_color
t_color_d	ray_to_color(const t_ray *ray)
{
	t_color_d	color;
	t_sphere	sphere;
	t_norm_ray	hit;
	
	sphere.center = (t_vec3){0.0, 0.0, -1.0};
	sphere.radius = 0.5;

	if (hit_sphere(&sphere, ray, 0.00001, 100000., &hit))
	{
		if (vec3_dot(ray->direction, hit.r.direction) > 0.0)
		{// ray is inside the sphere
			color = (t_color_d){1.0, 0.0, 1.0}; // magenta for inside
		}
		else
		{// ray is outside the sphere
			color = vec3_to_color_d(vec3_mul_one(vec3_add_one(hit.r.direction, 1), 0.5));
		}
	}
	else
	{
		// BACKGROUND COLORING (not hitting any sphere)
		t_vec3 norm_direction = vec3_normalize(ray->direction);
		double a = 0.5*(norm_direction.y + 1.0);
		
		color.r = (1.0 - a) *1.0 + (a * 0.5);
		color.g = (1.0 - a) *1.0 + (a * 0.7);
		color.b = (1.0 - a) *1.0 + (a * 1.0);
	}
	return (color);
}



