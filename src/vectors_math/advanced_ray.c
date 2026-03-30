/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced_ray.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:09:46 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	normalize_vec3_p(t_vec3 *a)
{
	double	length;

	length = length_vec3(*a);
	if (length == 0.0)
		return ;
	div_one_vec3_p(a, length);
}

t_vec3	get_pos_on_ray(const t_ray *ray, const double length)
{
	return (add_vec3(ray->origin, mul_one_vec3(ray->direction, length)));
}

t_vec3	reflect_vec3(const t_vec3 vector, const t_vec3 normal)
{
	return (sub_vec3(vector,
			mul_one_vec3(normal, 2 * dot_vec3(vector, normal))));
}

t_vec3	refract_vec3(const t_vec3 *unit_vector, const t_vec3 *normal,
		double etai_over_etat)
{
	t_vec3	r_out_perp;
	t_vec3	r_out_parallel;
	double	cos_theta;

	cos_theta = fmin(dot_vec3(inverse_vec3(*unit_vector), *normal), 1.0);
	r_out_perp = mul_one_vec3(add_vec3(*unit_vector,
				mul_one_vec3(*normal, cos_theta)), etai_over_etat);
	r_out_parallel = mul_one_vec3(*normal,
			-sqrt(fabs(1.0 - length_squared_vec3(r_out_perp))));
	return (add_vec3(r_out_perp, r_out_parallel));
}
