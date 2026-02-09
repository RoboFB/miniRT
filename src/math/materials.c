/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:56:22 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 19:27:57 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	scatter_lambertian(const t_norm_ray* hit, t_ray *scattered)
{

	t_vec3 scatter_direction = add_vec3(hit->r.direction, get_random_unit_vector());
	
	if (is_near_zero_vec3(scatter_direction))
		scatter_direction = hit->r.direction;
	
	*scattered = (t_ray){hit->r.origin, scatter_direction};
	return true;
}

bool	scatter_metal(const t_ray* r_in, const t_norm_ray* hit, t_ray *scattered)
{

	t_vec3 reflected = reflect_vec3(r_in->direction, hit->r.direction);
	*scattered = (t_ray){hit->r.origin, reflected};

	return true;
}

