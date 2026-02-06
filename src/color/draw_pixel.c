/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:42 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/06 12:48:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


// (x=r, y=g, z=b) takes 0.0 to 1.0, gamma corrects it and draws it to the pixel
void	img_draw_vec3(uint8_t* pixel, const t_vec3 *color_linear)
{
	pixel[0] = (uint8_t)(linear_to_gamma(color_linear->x) * 255);
	pixel[1] = (uint8_t)(linear_to_gamma(color_linear->y) * 255);
	pixel[2] = (uint8_t)(linear_to_gamma(color_linear->z) * 255);
	pixel[3] = 0xFF;
}

// only use if necessary, use img_draw_d if possible
void	img_draw_256(uint8_t* pixel, const t_color_256 *color)
{
	*(t_color_256*)pixel = *color;
}
