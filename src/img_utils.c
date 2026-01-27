/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 17:49:42 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 12:21:35 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Fills the image pixels with the color
void	img_fill_color(mlx_image_t *img, uint32_t color)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
			mlx_put_pixel(img, x++, y, color);
		y++;
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

// Updates the screen image with the current image
void	update_screen(t_gui *gui)
{
	img_copy(gui->img, gui->buffer_img);
	return ;
}