/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:42 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/13 19:46:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


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

// convert whit to black
void	img_white_to_black(mlx_image_t *change)
{
	uint32_t	pos;
	t_color_256	*pixel_buffer;
	
	pixel_buffer = (t_color_256 *)change->pixels;
	pos = 0;
	while (pos < change->height * change->width)
	{
		if (pixel_buffer[pos].value == WHITE_256.value)
		{
			img_draw_256(pixel_buffer[pos].bytes, &BLAKE_256);
		}
		pos++;
	}
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
