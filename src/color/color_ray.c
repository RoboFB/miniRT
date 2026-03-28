/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:15:08 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Traces a ray and returns its color, recursing up to depth bounces. */
t_vec3	ray_to_color(const t_ray *ray, int depth)
{
	t_norm_ray	hit;
	t_interval	ray_boarder;
	t_material	*hit_material;

	if (depth-- == 0)
		return ((t_vec3){0});
	ray_boarder = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ft_bzero(&hit, sizeof(t_norm_ray));
	hit_material = nearest_hit_all(ray, &ray_boarder, &hit);
	if (hit_material == NULL)
		return (background_color(ray));
	if (dot_vec3(ray->direction, hit.r.direction) > 0.0)
		return (inside_the_obj(hit_material, &hit, ray, depth));
	return (outside_the_obj(hit_material, &hit, ray, depth));
}

/* Returns a sky-gradient background color based on ray direction. */
t_vec3	background_color(const t_ray *ray)
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

/* Scatters a ray off a surface by material type and returns its color. */
t_vec3	outside_the_obj(const t_material *material, const t_norm_ray *hit,
		const t_ray *ray, int depth)
{
	t_ray	scattered;
	double	ri;

	scattered = (t_ray){0};
	ri = 0;
	if (material->type & MATERIAL_PHONG)
		return (phong_color(material, hit, ray));
	if ((material->type & MATERIAL_LAMBERTIAN)
		&& scatter_lambertian(hit, &scattered))
		return (mul_vec3(ray_to_color(&scattered, depth), material->color));
	if ((material->type & MATERIAL_REFLECTION)
		&& scatter_metal(ray, hit, &scattered, material))
		return (mul_vec3(ray_to_color(&scattered, depth), material->color));
	if (material->type & MATERIAL_DIELECTRIC)
	{
		ri = 1.0 / material->refraction_index;
		if (scatter_dielectric(ray, hit, &scattered, ri))
			return (mul_vec3(ray_to_color(&scattered, depth),
					(t_vec3){1.0, 1.0, 1.0}));
	}
	return ((t_vec3){0});
}

/* Handles ray scattering from inside an object (dielectric transmission). */
t_vec3	inside_the_obj(const t_material *material, t_norm_ray *hit,
		const t_ray *ray, int depth)
{
	t_ray	scattered;

	scattered = (t_ray){0};
	hit->r.direction = inverse_vec3(hit->r.direction);
	if (material->type & MATERIAL_PHONG)
		return (phong_color(material, hit, ray));
	if (material->type & MATERIAL_DIELECTRIC)
	{
		if (scatter_dielectric(ray, hit, &scattered,
				material->refraction_index))
			return (mul_vec3(ray_to_color(&scattered, depth),
					(t_vec3){1.0, 1.0, 1.0}));
	}
	return ((t_vec3){0});
}

/* Computes Phong shading: ambient, diffuse, and specular contributions. */
t_vec3	phong_color(const t_material *material, const t_norm_ray *hit,
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
			diffuse = fmax(dot_vec3(hit->r.direction, light_dir), 0.0);
			add_vec3_p(&color, mul_one_vec3(light->color,
					light->ratio * diffuse));
		}
		light++;
	}
	clamp_vec3_p(&color, (t_interval){0.0, 1.0});
	mul_vec3_p(&color, material->color);
	return (color);
}
