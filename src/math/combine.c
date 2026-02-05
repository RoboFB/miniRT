/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:04:46 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/05 11:18:00 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// x + y + z
double	vec3_combine(const t_vec3 a)
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