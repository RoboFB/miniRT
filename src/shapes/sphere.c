/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Tests whether a ray hits a sphere within the given interval. */
bool	is_hit_sphere(const t_sphere *sph, const t_ray *ray,
		const t_interval ray_boarder, t_norm_ray *hit)
{
	t_vec3	oc;
	double	a;
	double	h;
	double	disc;
	double	root;

	oc = sub_vec3(sph->center, ray->origin);
	a = length_squared_vec3(ray->direction);
	h = dot_vec3(ray->direction, oc);
	disc = h * h - a * (dot_vec3(oc, oc) - sph->radius * sph->radius);
	if (disc < 0)
		return (false);
	disc = sqrt(disc);
	root = (h - disc) / a;
	if (root <= ray_boarder.min || ray_boarder.max <= root)
	{
		root = (h + disc) / a;
		if (root <= ray_boarder.min || ray_boarder.max <= root)
			return (false);
	}
	hit->length = root;
	hit->r.origin = get_pos_on_ray(ray, hit->length);
	hit->r.direction = div_one_vec3(sub_vec3(hit->r.origin, sph->center),
			sph->radius);
	return (true);
}

/* Finds the nearest sphere hit across all spheres in the scene. */
t_sphere	*nearest_hit_sphere(const t_ray *ray, t_interval *ray_boarder,
		t_norm_ray *hit)
{
	t_sphere	*sphere_hit;
	t_sphere	*sphere_loop;

	sphere_hit = NULL;
	sphere_loop = get_scene()->spheres.first;
	while (sphere_loop != get_scene()->spheres.last)
	{
		if (is_hit_sphere(sphere_loop, ray, *ray_boarder, hit))
		{
			ray_boarder->max = hit->length;
			sphere_hit = sphere_loop;
		}
		sphere_loop++;
	}
	return (sphere_hit);
}

/* Returns a random unit vector in the hemisphere of the given normal. */
t_vec3	get_random_on_hemisphere(const t_vec3 *hit_direction_normal)
{
	t_vec3	new;

	new = get_random_unit_vector();
	if (dot_vec3(new, *hit_direction_normal) > 0.0)
		return (new);
	return (inverse_vec3(new));
}
