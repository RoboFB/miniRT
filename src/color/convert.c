/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:17 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/04 15:34:50 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color_d vec3_to_color_d(const t_vec3 v)
{
	t_color_d color;

	color.r = v.x;
	color.g = v.y;
	color.b = v.z;
	return (color);
}

t_color_256 color_d_to_256(const t_color_d color)
{
	t_color_256 result;


	result.r = (uint8_t)(color.r * 255);
	result.g = (uint8_t)(color.g * 255);
	result.b = (uint8_t)(color.b * 255);
	result.a = 0xFF;

	return (result);
}

t_color_d color_add(t_color_d a, t_color_d b)
{
	a.r += b.r;
	a.g += b.g;
	a.b += b.b;
	return (a);
}

t_color_d color_div_one(t_color_d a, double b)
{
	a.r /= b;
	a.g /= b;
	a.b /= b;
	return (a);
}
