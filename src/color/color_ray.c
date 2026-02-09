/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 18:04:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// aka ray_color
t_vec3	ray_to_color(const t_ray *ray, int depth)
{
	t_vec3		color;
	t_sphere	*sphere;
	t_norm_ray	hit = {0};
	
	
	
	if (depth-- == 0)
		return ((t_vec3){0.0, 0.0, 0.0});
	
	t_interval ray_boarder = {.min = 0.001, .max = HUGE_VAL};
	sphere = get_scene()->spheres.first;
	
	while (sphere != get_scene()->spheres.last)
	{
		if (is_hit_sphere(sphere, ray, ray_boarder, &hit)) // hit
		{
			ray_boarder.max = hit.length; // update ray boarder to closest hit
		}
		sphere++;
	}
	
	if (hit.length == 0.0)
	{
		// BACKGROUND COLORING (not hitting any sphere)
		t_vec3 norm_direction = normalize_vec3(ray->direction);
		double a = 0.5*(norm_direction.y + 1.0);
		
		color.x = (1.0 - a) *1.0 + (a * 0.5);
		color.y = (1.0 - a) *1.0 + (a * 0.7);
		color.z = (1.0 - a) *1.0 + (a * 1.0);
	}
	else if (dot_vec3(ray->direction, hit.r.direction) > 0.0)
	{// ray is inside the sphere
		color = (t_vec3){0.0, 0.0, 0.0}; // black for inside
	}
	else
	{// ray is outside the sphere
		
		t_vec3 direction = add_vec3(hit.r.direction, get_random_on_hemisphere(&hit.r.direction));
		color = mul_vec3_one(ray_to_color(&(t_ray){hit.r.origin, direction}, depth), 0.1);
		
		
		// color = vec3_to_color_d(mul_vec3_one(add_vec3_one(hit.r.direction, 1), 0.5));
	}
	
	return (color);
}



