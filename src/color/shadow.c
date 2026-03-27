/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/19 00:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/19 00:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Checks if hit->r.origin is in shadow of a light source.
// Sends a shadow ray from the hit point toward the light and tests
// if any sphere or plane lies in between.
// boarder.max = distance to light, so objects behind the light
// do not cast false shadows.
// Returns true if in shadow, false if lit.
bool	is_in_shadow(const t_norm_ray *hit, const t_light *light)
{
	t_ray		light_ray;
	t_interval	boarder;
	t_vec3		to_light;

	to_light = sub_vec3(light->position, hit->r.origin);
	light_ray = (t_ray){hit->r.origin, normalize_vec3(to_light)};
	boarder = (t_interval){SMALL_DOUBLE, length_vec3(to_light)};
	if (nearest_hit_sphere(&light_ray, &boarder, &(t_norm_ray){0}) != NULL)
		return (true);
	if (nearest_hit_plane(&light_ray, &boarder, &(t_norm_ray){0}) != NULL)
		return (true);
	return (false);
}
