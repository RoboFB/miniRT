/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/28 15:00:21 by rgohrig          ###   ########.fr       */
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



// x*x + y*y + z*z
t_vec3	vec3_square(t_vec3 a)
{
	a.x = a.x * a.x;
	a.y = a.y * a.y;
	a.z = a.z * a.z;
	return (a);
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
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}



t_vec3 vec3_fabs(const t_vec3 *a)
{
	t_vec3 result;

	result.x = fabs(a->x);
	result.y = fabs(a->y);
	result.z = fabs(a->z);
	return (result);
}



// origin + direction * t
t_vec3 ray_get_pos(const t_ray *ray, double t)
{
	t_vec3	result;
	
	result.x = ray->origin.x + ray->direction.x * t;
	result.y = ray->origin.y + ray->direction.y * t;
	result.z = ray->origin.z + ray->direction.z * t;
	return (result);
}



// broken ?
t_vec3	vec3_normalize(const t_vec3 *a)
{
	double	magnitude;
	t_vec3	result;
	
	result = vec3_mul(*a, *a);
	magnitude = sqrt(result.x + result.y + result.z);
	if (magnitude == 0.0)
	{
		result.x = 0.0;
		result.y = 0.0;
		result.z = 0.0;
	}
	else
	{
		result.x = a->x / magnitude;
		result.y = a->y / magnitude;
		result.z = a->z / magnitude;
	}
	return (result);
}