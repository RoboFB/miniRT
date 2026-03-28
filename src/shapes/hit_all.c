/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hit_all.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:12:37 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Returns the material of the closest shape hit (sphere, plane, cylinder). */
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
