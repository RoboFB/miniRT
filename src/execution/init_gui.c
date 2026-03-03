/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:52:51 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/03 17:56:26 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

void	init_gui_exit(t_gui *gui)
{
	gui->mlx = mlx_init(WIDTH_DEFAULT, HEIGHT_DEFAULT, "miniRT", true);
	if (!gui->mlx)
		perror_mlx_exit("Graphics: Window creation failed");
	
	gui->img = mlx_new_image(gui->mlx, WIDTH_DEFAULT, HEIGHT_DEFAULT);
	if (gui->img == NULL)
		perror_mlx_exit("Graphics: Image creation failed");
	img_fill_256(gui->img, &BLAKE_256);
	gui->img->enabled = false;
	if (mlx_image_to_window(gui->mlx, gui->img, 0, 0) < 0)
		perror_mlx_exit("Graphics: Image to Window failed");
		
	gui->buffer_img = mlx_new_image(gui->mlx, gui->img->width, gui->img->height);
	if (gui->buffer_img == NULL)
		perror_mlx_exit("Graphics: Buffer Image creation failed");
	img_fill_256(gui->buffer_img, &BLAKE_256);
	gui->buffer_img->enabled = true;
	if (mlx_image_to_window(gui->mlx, gui->buffer_img, 0, 0) < 0)
		perror_mlx_exit("Graphics: Image to Window failed");

	init_hooks(gui);
	return ;
}

