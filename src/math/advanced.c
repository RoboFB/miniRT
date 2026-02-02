/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/02 11:07:30 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a * -1
t_vec3	vec3_inverse(t_vec3 a)
{
	return (vec3_mul_one(a, -1));
}

// x*x + y*y + z*z
t_vec3	vec3_square(t_vec3 a)
{
	return (vec3_mul(a, a));
}

t_vec3 vec3_cross(const t_vec3 a, const t_vec3 b)
{
	t_vec3 result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3 vec3_fabs(const t_vec3 *a)
{
	t_vec3 result;

	result.x = fabs(a->x);
	result.y = fabs(a->y);
	result.z = fabs(a->z);
	return (result);
}

// convert some vector form length x to length 1 useing imaginary 0,0,0 point
t_vec3 vec3_normalize(t_vec3 a)
{
	double length;

	length = vec3_length(a);
	if (length == 0.0)
		return (a);
	return (vec3_div_one(a, length));
}

// origin + direction * t
t_vec3 ray_get_pos(const t_ray *ray, double length)
{
	return (vec3_add(ray->origin, vec3_mul_one(ray->direction, length)));
}
