/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/28 18:22:47 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// aka ray_color
t_color_d	ray_to_color(const t_ray *ray)
{
	// debug_ray("ray", ray);
	t_color_d color;


	t_vec3 center = {0.0, 0.0, -1.0};
	double hit = hit_sphere(center, 0.5, ray);
	// debug_decimal("hit", hit);
	if (hit > 0.0)
	// if (1)
	{
		printf("HIT SPHERE YES\n");
		t_vec3 tmp = vec3_sub(ray_get_pos(ray, hit),(t_vec3){0,0,-1});
		double length2 = sqrt(vec3_combine(vec3_square(tmp)));
		t_vec3 tmp2 = vec3_div_one(tmp, length2);

		

		color = vec3_to_color_d(vec3_mul_one(vec3_add_one(tmp2, 1.0), 0.5));
		return (color);
	}

	// debug_vec3("direction    ", &ray->direction);
	double length = sqrt(vec3_combine(vec3_square(ray->direction)));
	// debug_decimal("length", length);
	
	t_vec3 unit_direction = vec3_div_one(ray->direction, length); //?
	// debug_vec3("unit_direction", &unit_direction);
	double a = 0.5*(unit_direction.y + 1.0);

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