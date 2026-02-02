/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 12:20:24 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/02 16:45:01 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void init_frames(void)
{


}

// render function(gets called once after all params are set up)
void render(void)
{
	t_scene *scene = get_scene();
	mlx_image_t *img = get_gui()->img;
	

	t_ray *all = scene->all_rays;
	
	
	
	double scale = tan(degrees_to_radians(scene->camera->fov) * 0.5);
	double imageAspectRatio = (double)img->width / (double)img->height; // assuming width > height
	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			t_vec3 direction;
			direction.x = (-1.0 + (2.0 * ((x + 0.5) / (double)img->width)) ) * scale * imageAspectRatio;
			direction.y = ( 1.0 - (2.0 * ((y + 0.5) / (double)img->height))) * scale;
			direction.z = -1.0;

			all[x + y * img->width].origin = scene->camera->position;
			all[x + y * img->width].direction = direction;
		}
	}

	for (uint32_t y = 0; y < img->height; y++)
	{
		for (uint32_t x = 0; x < img->width; x++)
		{
			t_color_d color = ray_to_color(&all[x + y * img->width]);
			mlx_put_pixel(get_gui()->img, x, y, color_d_to_256(color).value);
		}
	}


	swap_screen_imgs(get_gui());
}

