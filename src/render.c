/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:20:24 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/05 11:44:27 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


void	get_ray_pix_center(mlx_image_t *img, t_camera *camera, uint32_t x, uint32_t y, t_ray *all)
{
	all[x + y * img->width].direction.x = camera->corner_upper_left.x + x * camera->delta_x;
	all[x + y * img->width].direction.y = camera->corner_upper_left.y - y * camera->delta_y;
	all[x + y * img->width].direction.z = -camera->focal_length;
	all[x + y * img->width].origin = camera->position;
}


void	fill_rays(mlx_image_t *img, t_camera *camera, t_ray *all)
{
	uint32_t	x;
	uint32_t	y;

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			get_ray_pix_center(img, camera, x, y, all);
			x++;
		}
		y++;
	}
}


// render function(gets called once after all params are set up)
void	render(void)
{
	t_scene		*scene;
	mlx_image_t	*img;
	t_color_d	color;
	uint32_t	pos;

	scene = get_scene();
	img = get_gui()->img;
	fill_rays(img, scene->camera, scene->all_rays);
	pos = 0;
	while (pos < img->height * img->width)
	{
		color = anti_alias(&scene->all_rays[pos], 64, scene->camera);
		img_draw_d(&img->pixels[pos * 4], &color);
		pos++;
	}
	swap_screen_imgs(get_gui());
}

// supersampling anti-aliasing but its math incorectly dont useses thr correct pixed divion pos for sampling 9 points
t_ray offset_ray(t_ray *ray, t_camera *camera)
{
	t_ray	new;

	new = *ray;
	new.direction.x += camera->delta_x * (0.5 - get_random());
	new.direction.y += camera->delta_y * (0.5 - get_random());
	// printf(" offset_x:%f offset_y:%f\n", offset_x/camera->delta_x, offset_y/camera->delta_y);
	return (new);
}




t_color_d anti_alias(t_ray *ray, uint32_t total, t_camera *camera)
{
	uint32_t	count;
	t_color_d	color;
	t_ray		tmp_ray;

	
	color = (t_color_d){0.0, 0.0, 0.0};
	count = 0;
	while (count < total)
	{
		tmp_ray = offset_ray(ray, camera);
		color = color_add(color, ray_to_color(&tmp_ray, camera->max_deep_rays));
		count++;
	}
	color = color_div_one(color, total);
	return (color);
}


