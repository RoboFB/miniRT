/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/05 12:12:49 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// aka ray_color
t_color_d	ray_to_color(const t_ray *ray, int depth)
{
	t_color_d	color;
	t_sphere	*sphere;
	t_norm_ray	hit = {0};
	
	
	
	if (depth-- == 0)
	return ((t_color_d){0.0, 0.0, 0.0});
	
	t_interval ray_boarder = {.min = 0.001, .max = HUGE_VAL};
	sphere = get_scene()->spheres.first;
	
	while (sphere != get_scene()->spheres.last)
	{
		if (hit_sphere(sphere, ray, ray_boarder, &hit)) // hit
		{
			ray_boarder.max = hit.length; // update ray boarder to closest hit
		}
		sphere++;
	}
	
	if (hit.length == 0.0)
	{
		// BACKGROUND COLORING (not hitting any sphere)
		t_vec3 norm_direction = vec3_normalize(ray->direction);
		double a = 0.5*(norm_direction.y + 1.0);
		
		color.r = (1.0 - a) *1.0 + (a * 0.5);
		color.g = (1.0 - a) *1.0 + (a * 0.7);
		color.b = (1.0 - a) *1.0 + (a * 1.0);
	}
	else if (vec3_dot(ray->direction, hit.r.direction) > 0.0)
	{// ray is inside the sphere
		color = (t_color_d){0.0, 0.0, 0.0}; // black for inside
	}
	else
	{// ray is outside the sphere
		
		t_vec3 direction = vec3_add(hit.r.direction, random_on_hemisphere(&hit.r.direction));
		color = color_div_one(ray_to_color(&(t_ray){hit.r.origin, direction}, depth), 2.0);
		
		
		// color = vec3_to_color_d(vec3_mul_one(vec3_add_one(hit.r.direction, 1), 0.5));
	}
	
	return (color);
}



