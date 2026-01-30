/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 13:47:07 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 11:24:43 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// R: color as uint32_t
uint32_t	fr_get_rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (
		((uint32_t)r << 24)
		| ((uint32_t)g << 16)
		| ((uint32_t)b << 8)
		| (uint32_t)a);
}

// R: True(same) False(different)
bool	fr_color_cmp(uint8_t *pixel_color, uint32_t check_color)
{
	return (
		fr_get_rgba(
			pixel_color[0],
			pixel_color[1],
			pixel_color[2],
			pixel_color[3])
		== check_color);
}

// R: True(same) False(different)
bool	fr_pixel_cmp(mlx_image_t *img, t_pixel *pix, uint32_t check_color)
{
	return (
		fr_color_cmp(
			&img->pixels[(pix->x + pix->y * img->width) * BPP],
			check_color));
}

// R: color out of iterations
uint32_t	fr_get_color(uint32_t iterations, uint32_t max_iterations,
		uint32_t color_offset)
{
	const double	frequency = 0.03;
	uint8_t			r;
	uint8_t			g;
	uint8_t			b;
	uint32_t		color;

	if (iterations == max_iterations)
		color = BLAKE;
	else
	{
		iterations += color_offset;
		r = (uint8_t)((sin(frequency * iterations + 0.000) * 127 + 128) * 0.7);
		g = (uint8_t)((sin(frequency * iterations + 2.094) * 127 + 128) * 0.7);
		b = (uint8_t)((sin(frequency * iterations + 4.188) * 127 + 128) * 0.7);
		color = fr_get_rgba(r, g, b, 255);
	}
	return (color);
}
