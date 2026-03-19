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

// Prueft ob der Punkt hit->r.origin im Schatten eines Lichts liegt.
// Schickt einen Shadow-Ray vom Hit-Punkt in Richtung Licht und testet
// ob eine Sphere oder Plane dazwischen liegt.
// boarder.max = Distanz zum Licht, damit Objekte hinter dem Licht
// keinen falschen Schatten werfen.
// true = im Schatten, false = beleuchtet
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
