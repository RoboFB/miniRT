/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 19:59:05 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// aka ray_color
t_vec3	ray_to_color(const t_ray *ray, int depth)
{
	t_vec3		color;
	t_sphere	*sphere_loop;
	t_sphere	*sphere_hit;
	t_norm_ray	hit = {0};
	
	
	
	if (depth-- == 0)
		return ((t_vec3){0.0, 0.0, 0.0});
	
	t_interval ray_boarder = {.min = 0.001, .max = HUGE_VAL};
	sphere_loop = get_scene()->spheres.first;
	sphere_hit = NULL;
	while (sphere_loop != get_scene()->spheres.last)
	{
		if (is_hit_sphere(sphere_loop, ray, ray_boarder, &hit)) // hit
		{
			ray_boarder.max = hit.length; // update ray boarder to closest hit
			sphere_hit = sphere_loop;
		}
		sphere_loop++;
	}

	if (sphere_hit == NULL)
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
	{// ray is outside the sphere and hits the sphere
		
		t_ray scattered = {0};
		if (sphere_hit->material.type == MATERIAL_LAMBERTIAN)
		{
			scatter_lambertian(&hit, &scattered);
			color = mul_vec3(ray_to_color(&scattered, depth), sphere_hit->material.albedo_color);
		}
		else if (sphere_hit->material.type == MATERIAL_METAL)
		{
			scatter_metal(ray, &hit, &scattered);
			color = mul_vec3(ray_to_color(&scattered, depth), sphere_hit->material.albedo_color);
		}
		else
		{
			color = (t_vec3){0.0, 0.0, 0.0}; // black for no material
		}
	}
	
	return (color);
}



