/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 18:03:29 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a * -1
t_vec3	inverse_vec3(const t_vec3 a)
{
	return (mul_vec3_one(a, -1));
}

// x*x + y*y + z*z
t_vec3	square_vec3(const t_vec3 a)
{
	return (mul_vec3(a, a));
}

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
	return (div_vec3_one(a, length));
}

// origin + direction * t
t_vec3 get_pos_on_ray(const t_ray *ray, const double length)
{
	return (add_vec3(ray->origin, mul_vec3_one(ray->direction, length)));
}
