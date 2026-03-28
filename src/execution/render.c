/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:20:24 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Triggers a full scene render into the current screen image. */
void	render(void)
{
	t_scene		*scene;
	mlx_image_t	*img;

	scene = get_scene();
	img = get_gui()->img;
	reset_render_time(get_gui());
	loop_rays(img, scene->camera);
	swap_screen_imgs(get_gui());
	update_stats(get_gui(), scene->camera);
}

/* Iterates over all pixels and calls sample_rays for each. */
void	loop_rays(mlx_image_t *img, t_camera *camera)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			sample_rays(x, y, img, camera);
			x++;
		}
		y++;
	}
}

/* Accumulates multiple ray samples for a pixel and writes averaged color. */
void	sample_rays(uint32_t x, uint32_t y, mlx_image_t *img,
		t_camera *camera)
{
	t_ray		tmp_ray;
	t_vec3		color;
	t_vec3		pixel_pos;
	uint32_t	count;

	color = (t_vec3){0};
	count = 0;
	pixel_pos = get_pix_pos_base(camera, x, y);
	while (count < camera->anti_aliasing_samples)
	{
		tmp_ray = final_ray(&pixel_pos, camera);
		add_vec3_p(&color, ray_to_color(&tmp_ray, camera->max_deep_rays));
		count++;
	}
	div_one_vec3_p(&color, camera->anti_aliasing_samples);
	img_draw_vec3(&img->pixels[(x + y * img->width) * 4], &color);
}

/* Returns the world-space center position of the given pixel. */
t_vec3	get_pix_pos_base(t_camera *camera, uint32_t x, uint32_t y)
{
	t_vec3	pixel_pos;

	pixel_pos = camera->corner_upper_left;
	add_vec3_p(&pixel_pos, mul_one_vec3(camera->delta_u, (double)x));
	add_vec3_p(&pixel_pos, mul_one_vec3(camera->delta_v, (double)y));
	if (x == 0 && y == 0)
		debug_vec3("top left    ", &pixel_pos);
	if (x == WIDTH_DEFAULT - 1 && y == HEIGHT_DEFAULT - 1)
		debug_vec3("bottom right", &pixel_pos);
	return (pixel_pos);
}

/* Constructs a camera ray through a pixel with a random sub-pixel offset. */
t_ray	final_ray(const t_vec3 *base, t_camera *camera)
{
	t_ray	new;

	new.direction = sub_vec3(*base, camera->ray.r.origin);
	add_vec3_p(&new.direction,
		mul_one_vec3(camera->delta_u, get_random() * 0.5));
	add_vec3_p(&new.direction,
		mul_one_vec3(camera->delta_v, get_random() * 0.5));
	new.origin = camera->ray.r.origin;
	return (new);
}
