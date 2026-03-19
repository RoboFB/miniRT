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
// true = im Schatten, false = beleuchtet
bool	is_in_shadow(const t_norm_ray *hit, const t_light *light)
{
	t_ray		light_ray;
	t_interval	boarder;

	light_ray = (t_ray){hit->r.origin, light->position};
	boarder = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	if (nearest_hit_sphere(&light_ray, &boarder, &(t_norm_ray){0}) != NULL)
		return (true);
	if (nearest_hit_plane(&light_ray, &boarder, &(t_norm_ray){0}) != NULL)
		return (true);
	return (false);
}
