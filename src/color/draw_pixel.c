/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_pixel.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:42 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:15:04 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Writes a gamma-corrected linear vec3 color into an image pixel. */
void	img_draw_vec3(uint8_t *pixel, const t_vec3 *color_linear)
{
	pixel[0] = (uint8_t)(linear_to_gamma(color_linear->x) * 255);
	pixel[1] = (uint8_t)(linear_to_gamma(color_linear->y) * 255);
	pixel[2] = (uint8_t)(linear_to_gamma(color_linear->z) * 255);
	pixel[3] = 0xFF;
}

/* Writes a 256-value RGBA color directly into an image pixel. */
void	img_draw_256(uint8_t *pixel, const t_color_256 *color)
{
	ft_memcpy(pixel, color, sizeof(t_color_256));
}
