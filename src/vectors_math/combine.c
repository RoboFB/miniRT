/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:04:46 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/30 12:41:37 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// x + y + z
double	combine_vec3(const t_vec3 a)
{
	return (a.x + a.y + a.z);
}

// dot product of a and b (x1*x2 + y1*y2 + z1*z2)
double	dot_vec3(const t_vec3 a, const t_vec3 b)
{
	return (combine_vec3(mul_vec3(a, b)));
}

// squared length of vector from 0,0,0 to a returns: (length * length)
double	length_squared_vec3(const t_vec3 a)
{
	return (combine_vec3(square_vec3(a)));
}

// length of vector from 0,0,0 to a
double	length_vec3(const t_vec3 a)
{
	return (sqrt(length_squared_vec3(a)));
}
