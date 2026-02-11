/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/11 15:20:28 by rgohrig          ###   ########.fr       */
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
	
	
	color = BLACK_VEC3; // black for default
	if (depth-- == 0)
		return (color);
	
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
		return color;
	}

	t_ray scattered = {0};
	
	if (dot_vec3(ray->direction, hit.r.direction) > 0.0)
	{// ray is inside the sphere
		hit.r.direction = inverse_vec3(hit.r.direction);

		if (sphere_hit->material.type == MATERIAL_DIELECTRIC)
		{
			double ri = sphere_hit->material.refraction_index;
			if (scatter_dielectric(ray, &hit, &scattered, ri))
				color = mul_vec3(ray_to_color(&scattered, depth), WHITE_VEC3);
		}
	}
	else
	{// ray is outside the sphere and hits the sphere
		if (sphere_hit->material.type == MATERIAL_LAMBERTIAN)
		{
			if (scatter_lambertian(&hit, &scattered))
				color = mul_vec3(ray_to_color(&scattered, depth), sphere_hit->material.color);
		}
		else if (sphere_hit->material.type == MATERIAL_METAL)
		{
			if (scatter_metal(ray, &hit, &scattered, &sphere_hit->material))
				color = mul_vec3(ray_to_color(&scattered, depth), sphere_hit->material.color);
		}
		else if (sphere_hit->material.type == MATERIAL_DIELECTRIC)
		{
			double ri = (1.0/sphere_hit->material.refraction_index);
			if (scatter_dielectric(ray, &hit, &scattered, ri))
				color = mul_vec3(ray_to_color(&scattered, depth), WHITE_VEC3);
		}
	}
	
	return (color);
}



