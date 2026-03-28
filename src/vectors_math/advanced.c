/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   advanced.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 14:18:52 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:09:37 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec3	inverse_vec3(const t_vec3 a)
{
	return (mul_one_vec3(a, -1));
}

t_vec3	square_vec3(const t_vec3 a)
{
	return (mul_vec3(a, a));
}

t_vec3	cross_vec3(const t_vec3 a, const t_vec3 b)
{
	t_vec3	result;

	result.x = a.y * b.z - a.z * b.y;
	result.y = a.z * b.x - a.x * b.z;
	result.z = a.x * b.y - a.y * b.x;
	return (result);
}

t_vec3	fabs_vec3(const t_vec3 *a)
{
	t_vec3	result;

	result.x = fabs(a->x);
	result.y = fabs(a->y);
	result.z = fabs(a->z);
	return (result);
}

t_vec3	normalize_vec3(const t_vec3 a)
{
	double	length;

	length = length_vec3(a);
	if (length == 0.0)
		return (a);
	return (div_one_vec3(a, length));
}
