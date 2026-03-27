/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/20 13:25:08 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"


// ray: the one ray that i test if it hit somting its the in start ray
// hit: the normalized ray on the hit form the hit (to/from not sure) center

// aka ray_color
t_vec3	ray_to_color(const t_ray *ray, int depth)
{
	t_norm_ray		hit;
	t_interval		ray_boarder;
	t_material		*hit_material;

	if (depth-- == 0)
		return (BLACK_VEC3);
	ray_boarder = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ft_bzero(&hit, sizeof(t_norm_ray));
	hit_material = nearest_hit_all(ray, &ray_boarder, &hit);
	if (hit_material == NULL)
		return (background_color(ray));
	else if (dot_vec3(ray->direction, hit.r.direction) > 0.0)
		return (inside_the_obj(hit_material, &hit, ray, depth));
	else
		return (outside_the_obj(hit_material, &hit, ray, depth));
}

t_vec3 background_color(const t_ray *ray)
{
	t_vec3 color;

	t_vec3 norm_direction = normalize_vec3(ray->direction);
	double a = 0.5*(norm_direction.y + 1.0);
	
	color.x = (1.0 - a) *1.0 + (a * 0.5);
	color.y = (1.0 - a) *1.0 + (a * 0.7);
	color.z = (1.0 - a) *1.0 + (a * 1.0);
	return (color);
	// return get_scene()->ambient_light->color; //altnative options
	// return BLACK_VEC3; //altnative options
}


t_vec3 outside_the_obj(const t_material *material, const t_norm_ray *hit, const t_ray *ray, int depth)
{
	t_ray scattered = {0};

	if (material->type & MATERIAL_PHONG)
	{
		return (phone_color(material, hit, ray));
	}
	if (material->type & MATERIAL_LAMBERTIAN)
	{
		if (scatter_lambertian(hit, &scattered))
			return (mul_vec3(ray_to_color(&scattered, depth), material->color));
	}
	else if (material->type & MATERIAL_REFLECTION)
	{
		if (scatter_metal(ray, hit, &scattered, material))
			return (mul_vec3(ray_to_color(&scattered, depth), material->color));
	}
	else if (material->type & MATERIAL_DIELECTRIC)
	{
		double ri = (1.0/material->refraction_index);
		if (scatter_dielectric(ray, hit, &scattered, ri))
			return (mul_vec3(ray_to_color(&scattered, depth), WHITE_VEC3));
	}
	return (BLACK_VEC3);
}

// not so importance mostly for dielectric materials(galas)
t_vec3 inside_the_obj(const t_material *material, t_norm_ray *hit, const t_ray *ray, int depth)
{
	t_ray scattered = {0};

	hit->r.direction = inverse_vec3(hit->r.direction);
	
	if (material->type & MATERIAL_PHONG)
	{
		return (phone_color(material, hit, ray));
	}
	if (material->type & MATERIAL_DIELECTRIC)
	{
		double ri = material->refraction_index;
		if (scatter_dielectric(ray, hit, &scattered, ri))
			return (mul_vec3(ray_to_color(&scattered, depth), WHITE_VEC3));
	}
	return (BLACK_VEC3);
}

// Phong lighting: ambient + diffuse per light with shadow test.
// For each light: is_in_shadow checks if any object blocks the light.
// Diffuse = max(dot(normal, light_dir), 0) * light_color * ratio.
// Final color is multiplied by the material color.
t_vec3	phone_color(const t_material *material, const t_norm_ray *hit,
		const t_ray *ray)
{
	t_vec3	color;
	t_light	*light;
	double	diffuse;
	t_vec3	light_dir;

	(void)ray;
	color = mul_one_vec3(get_scene()->ambient_light->color,
			get_scene()->ambient_light->ratio);
	light = get_scene()->lights.first;
	while (light != get_scene()->lights.last)
	{
		if (!is_in_shadow(hit, light))
		{
			light_dir = normalize_vec3(sub_vec3(light->position,
						hit->r.origin));
			diffuse = fmax(dot_vec3(hit->r.direction,
						light_dir), 0.0);
			add_vec3_p(&color, mul_one_vec3(light->color,
						light->ratio * diffuse));
		}
		light++;
	}
	clamp_vec3_p(&color, (t_interval){0.0, 1.0});
	mul_vec3_p(&color, material->color);
	return (color);
}
