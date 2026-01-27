/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 20:54:36 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

t_color_d	direction_to_color(const t_vec3 *direction)
{
	t_color_d color;

	
	print_vec3("direction    ", direction);
	double length = sqrt(vec3_combine(vec3_square(*direction)));
	printf("length      %f", length);
	
	t_vec3 unit_direction = vec3_div_one(*direction, length); //?
	print_vec3("unit_direction", &unit_direction);
	double a = 0.5*(unit_direction.y + 1.0);

	printf("_num:_          %f\n\n", a);
	color.r = (1.0 - a) *1.0 + (a * 0.5);
	color.g = (1.0 - a) *1.0 + (a * 0.7);
	color.b = (1.0 - a) *1.0 + (a * 1.0);


	return (color);
}

t_color_256 color_d_to_255(t_color_d color)
{
	t_color_256 result;


	result.r = (uint8_t)(color.r * 255);
	result.g = (uint8_t)(color.g * 255);
	result.b = (uint8_t)(color.b * 255);
	result.a = 0xFF;

	return (result);
}


// broken
t_color_256 get_color_from_vec3(t_vec3 *rayDirection)
{
	t_color_256 color;

	color.r = (uint8_t)((rayDirection->x) * 0.5 * 255);
	color.g = (uint8_t)((rayDirection->y) * 0.5 * 255);
	color.b = (uint8_t)((rayDirection->z) * 0.5 * 255);
	color.a = 0xFF;

	return (color);
}

// broken
t_color_256 get_color_test(int x, int y)
{
	t_color_256 color;

	color.r = (uint8_t)x;
	color.g = (uint8_t)y;
	color.b = 0x00;
	color.a = 0xFF;

	return (color);
}