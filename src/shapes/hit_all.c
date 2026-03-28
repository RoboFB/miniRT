/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 00:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/27 00:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Tests all objects in the scene and returns the material of the nearest hit.
// Planes, spheres, and cylinders share ray_boarder so the closest hit wins.
// Returns NULL if no object was hit.
t_material	*nearest_hit_all(const t_ray *ray, t_interval *ray_boarder,
		t_norm_ray *hit)
{
	t_material	*material;
	t_plane		*plane_hit;
	t_sphere	*sphere_hit;
	t_cylinder	*cy_hit;

	material = NULL;
	plane_hit = nearest_hit_plane(ray, ray_boarder, hit);
	if (plane_hit)
		material = &plane_hit->material;
	sphere_hit = nearest_hit_sphere(ray, ray_boarder, hit);
	if (sphere_hit)
		material = &sphere_hit->material;
	cy_hit = nearest_hit_cylinder(ray, ray_boarder, hit);
	if (cy_hit)
		material = &cy_hit->material;
	return (material);
}
