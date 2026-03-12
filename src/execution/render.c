/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:20:24 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/12 12:36:02 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// render function(gets called once after all params are set up)
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

void sample_rays(uint32_t x, uint32_t y, mlx_image_t *img, t_camera *camera)
{
	t_ray		tmp_ray;
	t_vec3		color;
	uint32_t	count;

	color = BLACK_VEC3;
	count = 0;


	t_vec3 pixel_pos = get_pix_pos_base(camera, x, y);
	// add camera ?

	while (count < camera->anti_aliasing_samples)
	{
		tmp_ray = final_ray(&pixel_pos, camera);
		add_vec3_p(&color, ray_to_color(&tmp_ray, camera->max_deep_rays));
		count++;
	}
	div_one_vec3_p(&color, camera->anti_aliasing_samples);
	img_draw_vec3(&img->pixels[(x + y*img->width) * 4], &color);
	return ;
}


// get pixel pos ray
t_vec3	get_pix_pos_base(t_camera *camera, uint32_t x, uint32_t y)
{
	t_vec3 pixel_pos;

	pixel_pos = camera->corner_upper_left;
	add_vec3_p(&pixel_pos, mul_one_vec3(camera->delta_u, (double)x));
	add_vec3_p(&pixel_pos, mul_one_vec3(camera->delta_v, (double)y));
	
	if (x == 0 && y == 0)
		debug_vec3("top left    ", &pixel_pos);
	if (x == WIDTH_DEFAULT -1 && y == HEIGHT_DEFAULT-1)
		debug_vec3("bottom right", &pixel_pos);

	return pixel_pos;
}

// sub sampling random
t_ray	final_ray(const t_vec3 *base, t_camera *camera)
{
	t_ray	new;

	new.direction = sub_vec3(*base, camera->ray.r.origin);
	add_vec3_p(&new.direction, mul_one_vec3(camera->delta_u, get_random()*0.5));
	add_vec3_p(&new.direction, mul_one_vec3(camera->delta_v, get_random()*0.5));

	new.origin = camera->ray.r.origin;
	return (new);
}




// tries early brake
// t_vec3 anti_alias(t_ray *ray, uint32_t total, t_camera *camera)
// {
// 	uint32_t	count;
// 	t_vec3		color;
// 	t_vec3		last_color;
// 	t_ray		tmp_ray;

	
// 	color = BLACK_VEC3;
// 	count = 0;
// 	while (count < total)
// 	{
// 		tmp_ray = offset_ray(ray, camera);
// 		color = add_vec3(color, ray_to_color(&tmp_ray, camera->max_deep_rays));
// 		if (is_interval_in((t_interval){-0.0001, 0.0001}, length_squared_vec3(vec3_div_one(color, count)) - length_squared_vec3(last_color)))
// 			break;
// 		last_color = color;
// 		count++;
// 	}
// 	color = vec3_div_one(color, total);
// 	return (color);
// }


// tries to find the color in the center but its worse than the average at the moment
// t_vec3 anti_alias(t_ray *ray, uint32_t total, t_camera *camera)
// {
// 	uint32_t	count;
// 	t_vec3		color;
// 	t_vec3		min = {0.0,0.0,0.0};
// 	t_vec3		max = {1.0,1.0,1.0};
// 	t_ray		tmp_ray;

	
// 	tmp_ray = offset_ray(ray, camera);
// 	min = ray_to_color(&tmp_ray, camera->max_deep_rays);
// 	tmp_ray = offset_ray(ray, camera);
// 	max = ray_to_color(&tmp_ray, camera->max_deep_rays);
// 	count = 0;
// 	while (count < total - 1)
// 	{
// 		tmp_ray = offset_ray(ray, camera);
// 		color = add_vec3(color, ray_to_color(&tmp_ray, camera->max_deep_rays));

// 		if (is_interval_in_vec3(color, min, max))
// 		{
// 			t_vec3 diff_min = sub_vec3(color, min);
// 			t_vec3 diff_max = sub_vec3(max, color);

// 			if (is_bigger_vec3(diff_min, diff_max))
// 				min = color;
// 			else 
// 				max = color;

// 		}

// 		count++;
// 	}
// 	color = vec3_div_one(add_vec3(max, min), 2);
// 	return (color);
// }


