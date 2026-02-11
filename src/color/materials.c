/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   materials.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 17:56:22 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/11 15:53:47 by rgohrig          ###   ########.fr       */
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


// Use Schlick's approximation for reflectance.
double	reflectance(double cosine, double refraction_idx)
{
	double r0 = (1 - refraction_idx) / (1 + refraction_idx);
	r0 = r0 * r0;
	return (r0 + (1 - r0) * pow((1 - cosine), 5));
}


bool scatter_dielectric(const t_ray* r_in, const t_norm_ray *hit, t_ray *scattered, double ri)
{
	t_vec3 direction;
	t_vec3 unit_direction = normalize_vec3(r_in->direction);

	double cos_theta = fmin(dot_vec3(inverse_vec3(unit_direction), hit->r.direction), 1.0);
	double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

	bool cannot_refrect = ri * sin_theta > 1.0;
	
	if (cannot_refrect || reflectance(cos_theta, ri) > get_random())
		direction = reflect_vec3(unit_direction, hit->r.direction);
	else
		direction = refract_vec3(&unit_direction, &hit->r.direction, ri);
	
	*scattered = (t_ray){hit->r.origin, direction};
	return true;
}
