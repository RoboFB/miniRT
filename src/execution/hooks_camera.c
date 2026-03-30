/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks_camera.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 19:03:15 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:13:26 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Translates the camera position based on WASD/QE key input. */
void	move_camera_pos(mlx_key_data_t key_data, t_gui *gui, t_camera *camera)
{
	if (key_data.key == MLX_KEY_W)
		camera->ray.r.origin.z -= 1;
	if (key_data.key == MLX_KEY_S)
		camera->ray.r.origin.z += 1;
	if (key_data.key == MLX_KEY_A)
		camera->ray.r.origin.x -= 1;
	if (key_data.key == MLX_KEY_D)
		camera->ray.r.origin.x += 1;
	if (key_data.key == MLX_KEY_SPACE)
		camera->ray.r.origin.y += 1;
	if (key_data.key == MLX_KEY_LEFT_SHIFT)
		camera->ray.r.origin.y -= 1;
	calculate_camera(gui->img, camera);
}

/* Rotates the camera direction based on arrow key input. */
void	move_camera_ang(mlx_key_data_t key_data, t_gui *gui, t_camera *camera)
{
	if (key_data.key == MLX_KEY_UP)
		camera->ray.r.direction.z -= 1;
	if (key_data.key == MLX_KEY_DOWN)
		camera->ray.r.direction.z += 1;
	if (key_data.key == MLX_KEY_LEFT)
		camera->ray.r.direction.x -= 1;
	if (key_data.key == MLX_KEY_RIGHT)
		camera->ray.r.direction.x += 1;
	normalize_vec3_p(&camera->ray.r.direction);
	calculate_camera(gui->img, camera);
}
