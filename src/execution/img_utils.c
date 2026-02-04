/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:42 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/04 15:48:33 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	img_draw_d(uint8_t* pixel, const t_color_d *color)
{
	pixel[0] = (uint8_t)(color->r * 255);
	pixel[1] = (uint8_t)(color->g * 255);
	pixel[2] = (uint8_t)(color->b * 255);
	pixel[3] = 0xFF;
}

// only use if necessary, use img_draw_d if possible
void	img_draw_256(uint8_t* pixel, const t_color_256 *color)
{
	*(t_color_256*)pixel = *color;
}


// Fills the image pixels with the color
void	img_fill_256(mlx_image_t *img, const t_color_256 *color)
{
	uint32_t	pos;

	pos = 0;
	while (pos < img->height * img->width)
	{
		img_draw_256(&img->pixels[pos * 4], color);
		pos++;
	}
	return ;
}

// Copies the pixels from source to change| Needs same size to work
void	img_copy(mlx_image_t *change, mlx_image_t *source)
{
	if (change->width != source->width || change->height != source->height)
		return ;
	ft_memcpy(change->pixels, source->pixels,
		(change->height * change->width * BPP));
	return ;
}


static void	swap_pointers(mlx_image_t** a, mlx_image_t** b)
{
	mlx_image_t*	tmp;
	
	tmp = *a;
	*a = *b;
	*b = tmp;
}

// Updates the screen image with the current image
void	swap_screen_imgs(t_gui *gui)
{
	gui->img->enabled = true;
	gui->buffer_img->enabled = false;
	swap_pointers(&gui->img, &gui->buffer_img);
	return ;
}
