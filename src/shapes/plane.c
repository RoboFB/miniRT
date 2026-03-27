/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <lihrig@student.42heilbronn.de>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/19 13:27:06 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Ray-plane intersection test.
// Example: a ground plane at y=-2 with upward normal (0,1,0)
//   pl 0,-2,0  0,1,0  0,255,0
// A downward ray hits it; a horizontal ray does not.
//
// Math: a point P lies on the plane if dot(P - plane.origin, normal) = 0
// Substituting the ray P(t) = ray.origin + t * ray.dir and solving for t:
//   t = dot(plane.origin - ray.origin, normal) / dot(ray.dir, normal)
//
// denom = dot(ray.dir, normal):
//   ~0 means the ray is parallel to the plane -> no hit
//   >0 means the ray hits from below (same side as the normal)
//   <0 means the ray hits from above (opposite side of the normal)
//
// Unlike spheres (quadratic, 0/1/2 hits), planes always have
// exactly 0 or 1 hit, and the normal is the same everywhere.
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

// Returns the nearest plane hit and updates ray_boarder and hit, or NULL.
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
