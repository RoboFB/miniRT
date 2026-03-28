/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:12:29 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Tests whether a ray hits an infinite plane within the given interval. */
bool	is_hit_plane(const t_plane *pl, const t_ray *ray,
		const t_interval ray_boarder, t_norm_ray *hit)
{
	double	denom;
	t_vec3	oc;
	double	t;

	denom = dot_vec3(ray->direction, pl->plane.direction);
	if (fabs(denom) < SMALL_DOUBLE)
		return (false);
	oc = sub_vec3(pl->plane.origin, ray->origin);
	t = dot_vec3(oc, pl->plane.direction) / denom;
	if (t <= ray_boarder.min || ray_boarder.max <= t)
		return (false);
	hit->length = t;
	hit->r.origin = get_pos_on_ray(ray, t);
	hit->r.direction = pl->plane.direction;
	return (true);
}

/* Finds the nearest plane hit across all planes in the scene. */
t_plane	*nearest_hit_plane(const t_ray *ray, t_interval *ray_boarder,
		t_norm_ray *hit)
{
	t_plane	*plane_hit;
	t_plane	*plane_loop;

	plane_hit = NULL;
	plane_loop = get_scene()->planes.first;
	while (plane_loop != get_scene()->planes.last)
	{
		if (is_hit_plane(plane_loop, ray, *ray_boarder, hit))
		{
			ray_boarder->max = hit->length;
			plane_hit = plane_loop;
		}
		plane_loop++;
	}
	return (plane_hit);
}
