/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:56:22 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/11 14:58:14 by rgohrig          ###   ########.fr       */
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

bool	scatter_metal(const t_ray* r_in, const t_norm_ray* hit, t_ray *scattered, const t_material *material)
{

	t_vec3 reflected = reflect_vec3(r_in->direction, hit->r.direction);
	reflected = normalize_vec3(reflected);
	reflected = add_vec3(reflected, mul_vec3_one(get_random_unit_vector(), material->fuzz));
	*scattered = (t_ray){hit->r.origin, reflected};

	return (dot_vec3(scattered->direction, hit->r.direction) > 0);
}

bool scatter_dielectric(const t_ray* r_in, const t_norm_ray *hit, t_ray *scattered, double ri)
{
	t_vec3 unit_direction = normalize_vec3(r_in->direction);
	t_vec3 refracted = refract_vec3(&unit_direction, &hit->r.direction, ri);

	*scattered = (t_ray){hit->r.origin, refracted};
	return true;
}
