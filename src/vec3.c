/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/30 11:49:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a + b
t_vec3	vec3_add(t_vec3 a, t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

// a - b
t_vec3	vec3_sub(t_vec3 a, t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

// a * b
t_vec3	vec3_mul(t_vec3 a, t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

// a / b
t_vec3	vec3_div(t_vec3 a, t_vec3 b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return (a);
}

// a + add
t_vec3	vec3_add_one(t_vec3 a, double add)
{
	a.x += add;
	a.y += add;
	a.z += add;
	return (a);
}

// a - subtract
t_vec3	vec3_sub_one(t_vec3 a, double subtract)
{
	a.x -= subtract;
	a.y -= subtract;
	a.z -= subtract;
	return (a);
}

// a * multiply
t_vec3	vec3_mul_one(t_vec3 a, double multiply)
{
	a.x *= multiply;
	a.y *= multiply;
	a.z *= multiply;
	return (a);
}

// a / divide
t_vec3	vec3_div_one(t_vec3 a, double divide)
{
	a.x /= divide;
	a.y /= divide;
	a.z /= divide;
	return (a);
}

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

// x + y + z
double	vec3_combine(t_vec3 a)
{
	return (a.x + a.y + a.z);
}

// dot product of a and b (x1*x2 + y1*y2 + z1*z2)
double	vec3_dot(const t_vec3 a, const t_vec3 b)
{
	return (vec3_combine(vec3_mul(a, b)));
}

// squared length of vector from 0,0,0 to a returns: (length * length)
double vec3_length_squared(const t_vec3 a)
{
	return (vec3_combine(vec3_square(a)));
}

// length of vector from 0,0,0 to a
double vec3_length(const t_vec3 a)
{
	return (sqrt(vec3_length_squared(a)));
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

double degrees_to_radians(double degrees)
{
	return (degrees * (M_PI / 180.0));
}