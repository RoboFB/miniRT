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

// Ray-Plane Schnitttest.
// Beispiel: eine Bodenebene bei y=-2 mit Normale nach oben (0,1,0)
//   pl 0,-2,0  0,1,0  0,255,0
// Ein Ray nach unten trifft sie, ein horizontaler Ray nicht.
//
// Mathe: ein Punkt P liegt auf der Ebene wenn dot(P - plane.origin, normal) = 0
// Ray einsetzen P(t) = ray.origin + t * ray.dir und nach t aufloesen:
//   t = dot(plane.origin - ray.origin, normal) / dot(ray.dir, normal)
//
// denom = dot(ray.dir, normal):
//   ~0 heisst der Ray ist parallel zur Ebene -> kein Hit
//   >0 heisst der Ray trifft von unten (gleiche Seite wie Normale)
//   <0 heisst der Ray trifft von oben (gegenueber der Normale)
//
// Anders als Spheres (quadratisch, 0/1/2 Hits) haben Planes immer
// genau 0 oder 1 Hit, und die Normale ist ueberall gleich.
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

//eie naechste Plane und aktualisiert ray_boarder und hit, oder NULL same logic that you applied for  sphere
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
