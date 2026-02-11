/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:56:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/11 15:16:34 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"



// R: 0 = success, else error
int init_scene(t_scene *scene, int argc, char const *argv[])
{
	// TODO: implement parsing here.
	(void)argc;
	(void)argv;

	scene->camera = init_camera(get_gui()->img);

	scene->all_rays = ft_calloc(get_gui()->img->width * get_gui()->img->height, sizeof(t_ray));// todo: implement null check

	scene->spheres = dynamic_array_init(sizeof(t_sphere));

	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // left
		.center = (t_vec3){-0.5, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.1, 0.000001, 0.1},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // ground
		.center = (t_vec3){0.0, -100.5, -1.0},
		.radius = 100.0,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.fuzz = 0.01,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // glass
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.5,
		},
	});

	
	return (0);
}


t_camera	*init_camera(mlx_image_t *img)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));// todo: implement null check
	camera->position = BLACK_VEC3;
	camera->orientation = BLACK_VEC3;
	camera->fov = 90.0;
	camera->focal_length = 1.0;
	camera->max_deep_rays = 16;
	camera->anti_aliasing_samples = 2; // *2 in main hock
	
	// double scale = tan(degrees_to_radians(camera->fov) * 0.5); //TODO: implment FOV

	double viewport_height = 2.0;
	double imageAspectRatio = (double)img->width / (double)img->height;
	double viewport_width = viewport_height * imageAspectRatio;

	camera->delta_x = viewport_width / (double)(img->width);
	camera->delta_y = viewport_height / (double)(img->height);
	
	camera->corner_upper_left.x = -viewport_width / 2.0 + camera->delta_x / 2.0;
	camera->corner_upper_left.y = viewport_height / 2.0 - camera->delta_y / 2.0;
	camera->corner_upper_left.z = -camera->focal_length;
	
	return (camera);
}

