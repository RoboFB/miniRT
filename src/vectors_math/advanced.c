/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/12 12:21:29 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a * -1
t_vec3	inverse_vec3(const t_vec3 a)
{
	return (mul_one_vec3(a, -1));
}

// x*x + y*y + z*z
t_vec3	square_vec3(const t_vec3 a)
{
	return (mul_vec3(a, a));
}

// a b sequence important
t_vec3 cross_vec3(const t_vec3 a, const t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3 fabs_vec3(const t_vec3 *a)
{
	t_vec3 result;

	result.x = fabs(a->x);
	result.y = fabs(a->y);
	result.z = fabs(a->z);
	return (result);
}

// convert some vector form length x to length 1 useing imaginary 0,0,0 point
t_vec3 normalize_vec3(const t_vec3 a)
{
	double length;

	length = length_vec3(a);
	if (length == 0.0)
		return (a);
	return (div_one_vec3(a, length));
}

// convert some vector form length x to length 1 useing imaginary 0,0,0 point
void normalize_vec3_p(t_vec3 *a)
{
	double length;

	length = length_vec3(*a);
	if (length == 0.0)
		return ;
	div_one_vec3_p(a, length);
}

// origin + direction * t
t_vec3 get_pos_on_ray(const t_ray *ray, const double length)
{
	return (add_vec3(ray->origin, mul_one_vec3(ray->direction, length)));
}

t_vec3 reflect_vec3(const t_vec3 vector, const t_vec3 normal)
{
	return sub_vec3(vector, mul_one_vec3(normal, 2 * dot_vec3(vector, normal)));
}

t_vec3 refract_vec3(const t_vec3* unit_vector, const t_vec3 *normal, double etai_over_etat)
{
	double cos_theta = fmin(dot_vec3(inverse_vec3(*unit_vector), *normal), 1.0);
	t_vec3 r_out_perp =  mul_one_vec3(add_vec3(*unit_vector, mul_one_vec3(*normal, cos_theta)), etai_over_etat);
	t_vec3 r_out_parallel = mul_one_vec3(*normal, -sqrt(fabs(1.0 - length_squared_vec3(r_out_perp))));
	return add_vec3(r_out_perp, r_out_parallel);
}

