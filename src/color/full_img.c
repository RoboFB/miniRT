/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   full_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:42 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Fills an entire MLX image with a solid 8-bit RGBA color. */
void	img_fill_256(mlx_image_t *img, const t_color_256 *color)
{
	uint32_t	pos;

	pos = 0;
	while (pos < img->height * img->width)
	{
		img_draw_256(&img->pixels[pos * 4], color);
		pos++;
	}
}

/* Copies all pixel data from one MLX image to another. */
void	img_copy(mlx_image_t *change, mlx_image_t *source)
{
	if (change->width != source->width || change->height != source->height)
		return ;
	ft_memcpy(change->pixels, source->pixels,
		(change->height * change->width * BPP));
}

/* Replaces every white pixel in the image with black. */
void	img_white_to_black(mlx_image_t *change)
{
	uint32_t	pos;
	t_color_256	*pixel_buffer;

	pixel_buffer = (t_color_256 *)change->pixels;
	pos = 0;
	while (pos < change->height * change->width)
	{
		if (pixel_buffer[pos].value == g_white.value)
			img_draw_256(pixel_buffer[pos].bytes, &g_black);
		pos++;
	}
}

static void	swap_pointers(mlx_image_t **a, mlx_image_t **b)
{
	mlx_image_t	*tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

/* Swaps the two screen images in the GUI double-buffer. */
void	swap_screen_imgs(t_gui *gui)
{
	gui->img->enabled = true;
	gui->buffer_img->enabled = false;
	swap_pointers(&gui->img, &gui->buffer_img);
}
