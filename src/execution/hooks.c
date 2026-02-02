/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:03:15 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/30 14:11:04 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Main hook function, called every frame

void	hook_main(void *gui_void)
{
	const t_gui	*gui = gui_void;

	(void)gui;
	// if (mlx_get_time() > 20.0)// run for 20 seconds max for testing
	// 	mlx_close_window(gui->mlx);
	return ;
}

// R: void or error_exit
void	add_hooks(t_gui *gui)
{
	if (!mlx_loop_hook(gui->mlx, hook_main, gui))
		msg_exit("mlx: adding main loop as hook failed");
	mlx_key_hook(gui->mlx, hook_key, gui);
	// mlx_scroll_hook(gui->mlx, fr_hook_scroll, gui);
	// mlx_resize_hook(gui->mlx, fr_hook_resize, gui);
	return ;
}

// Key hook function, called on key presses
void	hook_key(mlx_key_data_t key_data, void *gui_void)
{
	const t_gui	*gui = gui_void;

	if (key_data.action == MLX_PRESS)
	{
		if (key_data.key == MLX_KEY_ESCAPE)
			mlx_close_window(gui->mlx);
	}
	return ;
}

// // Scroll hook function, called on mouse scroll
// void	fr_hook_scroll(double xdelta, double ydelta, void *gui_void)
// {
// 	t_data		*gui;
// 	t_pixel		pix_m;
// 	t_vec3		pos_m;
// 	double		zoom;

// 	gui = (t_data *)gui_void;
// 	(void)xdelta;
// 	if (ydelta > 0.0)
// 		zoom = pow(1.1, ydelta);
// 	else
// 		zoom = pow(0.9, -ydelta);
// 	gui->width_view *= zoom;
// 	gui->height_view *= zoom;
// 	mlx_get_mouse_pos(gui->mlx, (int *)&pix_m.x, (int *)&pix_m.y);
// 	if (pix_m.x < gui->img->width
// 		&& pix_m.y < gui->img->height)
// 	{
// 		fr_map_cplx(gui, &pix_m, &pos_m);
// 		gui->center_view.x
// 			= pos_m.x + (gui->center_view.x - pos_m.x) * zoom;
// 		gui->center_view.yi
// 			= pos_m.yi + (gui->center_view.yi - pos_m.yi) * zoom;
// 	}
// 	fr_reset_moved(gui);
// 	return ;
// }

// // Resize hook function, called on window resize
// void	fr_hook_resize(int32_t width, int32_t height, void *gui_void)
// {
// 	t_data		*gui;

// 	gui = (t_data *)gui_void;
// 	if ((width != (int)gui->img->width || height != (int)gui->img->height)
// 		&& width >= 30 && height >= 30
// 		&& width * height < MAX_CIR_QUEUE_SIZE)
// 	{
// 		if (!mlx_resize_image(gui->img, width, height))
// 			fr_error_exit(gui, "Resize image failed");
// 		if (!mlx_resize_image(gui->screen_img, width, height))
// 			fr_error_exit(gui, "Resize image failed");
// 	}
// 	fr_reset_moved(gui);
// 	return ;
// }
