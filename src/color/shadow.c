/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:14:48 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Returns true if the hit point is occluded from the given light source. */
bool	is_in_shadow(const t_norm_ray *hit, const t_light *light)
{
	t_ray		light_ray;
	t_interval	boarder;
	t_vec3		to_light;

	to_light = sub_vec3(light->position, hit->r.origin);
	light_ray = (t_ray){hit->r.origin, normalize_vec3(to_light)};
	boarder = (t_interval){SMALL_DOUBLE, length_vec3(to_light)};
	return (nearest_hit_all(&light_ray, &boarder, &(t_norm_ray){0}) != NULL);
}
