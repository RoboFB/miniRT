/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:03:15 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/10 17:38:21 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Main hook function, called every frame

void	hook_main(void *gui_void)
{
	const t_gui	*gui = gui_void;

	(void)gui;
	get_scene()->camera->anti_aliasing_samples *= 2;
	render();
	// if (mlx_get_time() > 20.0)// run for 20 seconds max for testing
	// 	mlx_close_window(gui->mlx);
	return ;
}

// R: void or error_exit
void	init_hooks(t_gui *gui)
{
	if (!mlx_loop_hook(gui->mlx, hook_main, gui))
		perror_mlx_exit("Adding main loop as hook failed");
	mlx_key_hook(gui->mlx, hook_key, gui);
	// mlx_scroll_hook(gui->mlx, fr_hook_scroll, gui);
	mlx_resize_hook(gui->mlx, hook_resize, gui);
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

// Resize hook function, called on window resize
void	hook_resize(int32_t width, int32_t height, void *gui_void)
{
	t_gui		*gui;

	gui = gui_void;
	if ((width == (int32_t)gui->img->width && height == (int32_t)gui->img->height)
		|| width < 1 || height < 1)//TODO: check if i need to guard for with < hight
		return ;
	if (!mlx_resize_image(gui->img, width, height))
		perror_mlx_exit("Resize image failed");
	if (!mlx_resize_image(gui->buffer_img, width, height))
		perror_mlx_exit("Resize image failed");

	// todo: abstract later

	free(get_scene()->all_rays);
	get_scene()->all_rays = ft_calloc(gui->img->width * gui->img->height, sizeof(t_ray));
	free(get_scene()->camera);
	get_scene()->camera = init_camera(gui->img);

	render();
	return ;
}
