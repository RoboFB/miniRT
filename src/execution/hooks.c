/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:03:15 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:13:19 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Per-frame callback: re-renders when the camera is marked dirty. */
static void	hook_main(void *gui_void)
{
	(void)gui_void;
	render();
}

/* Registers all MLX event hooks (key, resize, per-frame). */
void	init_hooks(t_gui *gui)
{
	if (!mlx_loop_hook(gui->mlx, hook_main, gui))
		perror_mlx_exit("Adding main loop as hook failed");
	mlx_key_hook(gui->mlx, hook_key, gui);
	mlx_resize_hook(gui->mlx, hook_resize, gui);
}

/* Handles key events: camera movement, quit, and render-mode toggles. */
void	hook_key(mlx_key_data_t key_data, void *gui_void)
{
	t_gui	*gui;

	gui = gui_void;
	if (key_data.action != MLX_PRESS)
		return ;
	if (key_data.key == MLX_KEY_ESCAPE)
		mlx_close_window(gui->mlx);
	if (key_data.key == MLX_KEY_I)
	{
		gui->statistics.type++;
		if (gui->statistics.type >= STATS_MAX)
			gui->statistics.type = STATS_RAYS_SEC;
	}
	move_camera_pos(key_data, gui, get_scene()->camera);
	move_camera_ang(key_data, gui, get_scene()->camera);
}

/* Handles window resize by recreating images and re-rendering. */
void	hook_resize(int32_t width, int32_t height, void *gui_void)
{
	t_gui	*gui;

	gui = gui_void;
	if ((width == (int32_t)gui->img->width
			&& height == (int32_t)gui->img->height)
		|| width < 1 || height < 1)
		return ;
	if (!mlx_resize_image(gui->img, width, height))
		perror_mlx_exit("Resize image failed");
	if (!mlx_resize_image(gui->buffer_img, width, height))
		perror_mlx_exit("Resize image failed");
	calculate_camera(gui->img, get_scene()->camera);
	render();
}
