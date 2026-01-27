/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 11:52:51 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 12:29:59 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

void	init_gui(t_gui *gui)
{
	gui->mlx = mlx_init(WIDTH_DEFAULT, HEIGHT_DEFAULT, "miniRT", true);
	if (!gui->mlx)
		msg_exit("Graphics: Window creation failed");
	
	gui->img = mlx_new_image(gui->mlx, WIDTH_DEFAULT, HEIGHT_DEFAULT);
	if (gui->img == NULL)
		msg_exit("Graphics: Image creation failed");
	gui->buffer_img = mlx_new_image(gui->mlx, WIDTH_DEFAULT, HEIGHT_DEFAULT);
	if (gui->buffer_img == NULL)
		msg_exit("Graphics: Screen Image creation failed");
	img_fill_color(gui->buffer_img, BLAKE);
	img_copy(gui->img, gui->buffer_img);

	if (mlx_image_to_window(gui->mlx, gui->img, 0, 0) < 0)
		msg_exit("Graphics: Image to Window failed");
	return ;
}

void	init_data(t_data *data)
{
	init_gui(&data->gui);
}
