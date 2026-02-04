/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:20:24 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/04 15:50:01 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	fill_rays(mlx_image_t *img, t_camera *camera, t_ray *all)
{
	uint32_t	x;
	uint32_t	y;

	// // assuming width > height
	
	

	y = 0;
	while (y < img->height)
	{
		x = 0;
		while (x < img->width)
		{
			all[x + y * img->width].direction.x = camera->corner_upper_left.x + x * camera->delta_x;
			all[x + y * img->width].direction.y = camera->corner_upper_left.y - y * camera->delta_y;
			all[x + y * img->width].direction.z = -camera->focal_length;
			all[x + y * img->width].origin = camera->position;
			x++;
		}
		y++;
	}
}

// void	fill_rays(mlx_image_t *img, t_camera *camera, t_ray *all)
// {
// 	uint32_t	x;
// 	uint32_t	y;
// 	// double		scale;
// 	double		imageAspectRatio;

// 	// assuming width > height
// 	// scale = tan(degrees_to_radians(camera->fov) * 0.5);
// 	imageAspectRatio = (double)img->width / (double)img->height;
	
// 	y = 0;
// 	while (y < img->height)
// 	{
// 		x = 0;
// 		while (x < img->width)
// 		{
// 			all[x + y * img->width].direction.x = 
// 				(-1.0 + (2.0 * ((x + 0.5) / (double)img->width))) * imageAspectRatio;
// 			all[x + y * img->width].direction.y = 
// 				(1.0 - (2.0 * ((y + 0.5) / (double)img->height)));
// 			all[x + y * img->width].direction.z = -1.0;
// 			all[x + y * img->width].origin = camera->position;
// 			x++;
// 		}
// 		y++;
// 	}
// }

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
		// HIER WEITETR MACHEN !!!! 
		t_ray	ray = scene->all_rays[pos];
		// ray.direction.x -= scene->camera->delta_x / 2.0;
		// ray.direction.y -= scene->camera->delta_y / 2.0;
		// color = ray_to_color(&ray);
		// ray.direction.y += scene->camera->delta_y;
		// color = color_add(color, ray_to_color(&ray));
		// ray.direction.x += scene->camera->delta_x;
		// color = color_add(color, ray_to_color(&ray));
		// ray.direction.y -= scene->camera->delta_y;
		// color = color_add(color, ray_to_color(&ray));
		color = anti_alias(ray, 2, scene->camera);

		// color = color_div_one(color, 4.0);
		img_draw_d(&img->pixels[pos * 4], &color);
		pos++;
	}
	swap_screen_imgs(get_gui());
}

// supersampling anti-aliasing but its math incorectly dont useses thr correct pixed divion pos for sampling 9 points
t_color_d anti_alias(t_ray ray, uint32_t size, t_camera *camera)
{
	t_color_d	color;
	uint32_t x;
	uint32_t y;

	ray.direction.x -= camera->delta_x / 2.0;
	ray.direction.y -= camera->delta_y / 2.0;

	color = (t_color_d){0.0, 0.0, 0.0};
	y = 0;
	while (y < size)
	{
		x = 0;
		while (x < size)
		{
			color = color_add(color, ray_to_color(&ray));

			ray.direction.x += camera->delta_x / size;
			x++;
		}
		ray.direction.x -= camera->delta_x;
		ray.direction.y += camera->delta_y / size;
		y++;
	}
	


	color = color_div_one(color, size*size);
	return (color);
}