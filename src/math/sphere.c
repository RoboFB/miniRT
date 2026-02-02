/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/30 14:33:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"



bool	hit_sphere(const t_sphere *sph, const t_ray *ray, double ray_min, double ray_max, t_norm_ray *hit)
{
	t_vec3 oc = vec3_sub(sph->center, ray->origin);
	double a = vec3_length_squared(ray->direction);
	double h = vec3_dot(ray->direction, oc);
	double c = vec3_length_squared(oc) - sph->radius*sph->radius;
	double discriminant_squad = (h*h) - (a*c);
	// printf("discriminant: %f, a;%f, b;%f, c;%f\n", discriminant, a, b, c);	
	// debug_decimal("22 discriminant", discriminant);

	if (discriminant_squad < 0)
		return (false);

	double discriminant = sqrt(discriminant_squad);
	

	double root = (h - discriminant) / a;
	if (root <= ray_min || ray_max <= root)
	{
		root = (h + discriminant) / a;
		if (root <= ray_min || ray_max <= root)
			return false;
	}

	hit->length = root;// is length factor of a norm ray
	hit->r.origin = ray_get_pos(ray, hit->length);
	hit->r.direction = vec3_div_one(vec3_sub(hit->r.origin, sph->center), sph->radius);
	// printf("l:%.3f,", vec3_length(hit->r.direction));
	// printf("%.3f\n",hit->length);

	return (true);
}

