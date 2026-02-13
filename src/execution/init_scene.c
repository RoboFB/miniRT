/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:56:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/13 14:40:08 by rgohrig          ###   ########.fr       */
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

	// init_sphere(scene);
	// test_fov(scene);
	puple_spheres(scene);

	
	return (0);
}

void	puple_spheres(t_scene *scene)
{
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
			.type = MATERIAL_METAL,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.fuzz = 0.01,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // in 0.4r 1.5
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.4,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.0/1.5,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){ // out 0.5r 1.0
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.0,
		},
	});
}

void init_sphere(t_scene *scene)
{
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){0.0, -100.5, -1.0},
		.radius = 100.0,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.8, 0.8, 0.0},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){0.0, 0.0, -1.2},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.1, 0.2, 0.5},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){-1.0, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.refraction_index = 1.50,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){-1.0, 0.0, -1.0},
		.radius = 0.4,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.refraction_index = 1.0 / 1.50,
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){1.0, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_METAL,
			.color = (t_vec3){0.8, 0.6, 0.2},
			.fuzz = 1,
		},
	});
}


void test_fov(t_scene *scene)
{
	double radius = cos(M_PI/4.0);

	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){-radius, 0.0, -1.0},
		.radius = radius,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.0, 0.0, 1.0},
		},
	});
	dynamic_array_add_back(&scene->spheres, &(t_sphere){
		.center = (t_vec3){radius, 0.0, -1.0},
		.radius = radius,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){1.0, 0.0, 0.0},
		},
	});
}


t_camera	*init_camera(mlx_image_t *img)
{
	t_camera	*camera;

	camera = ft_calloc(1, sizeof(t_camera));// todo: implement null check
	camera->ray.r.origin = (t_vec3){-2.0, 2.0, 1.0};
	camera->ray.r.direction = (t_vec3){1.0, -1.0,-1.0};
	camera->ray.length = 1.0; // focal length
	camera->fov = 90.0;
	camera->max_deep_rays = 16;
	camera->anti_aliasing_samples = 2; // *2 in main hock

	
	double scale = tan(degrees_to_radians(camera->fov) * 0.5);
	
	double viewport_height = 2.0 * scale * camera->ray.length;
	double imageAspectRatio = (double)img->width / (double)img->height;
	double viewport_width = viewport_height * imageAspectRatio;
	

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	t_vec3 vup = (t_vec3){0.0, 1.0, 0.0}; // relative up for changeing angels later if needed
	t_vec3 w = normalize_vec3(camera->ray.r.direction); //z
	t_vec3 u = normalize_vec3(cross_vec3(vup, w)); // x
	t_vec3 v = cross_vec3(w, u); //y

	t_vec3 viewport_u = mul_one_vec3(u, viewport_width);
	t_vec3 viewport_v = mul_one_vec3(v, viewport_height);

	camera->delta_u = div_one_vec3(viewport_u, (double)(img->width));
	camera->delta_v = div_one_vec3(viewport_v, (double)(img->height));
	
	// Start at focal point (in front of camera), then move to upper-left corner
	camera->corner_upper_left = add_vec3(camera->ray.r.origin, mul_one_vec3(w, camera->ray.length));
	debug_vec3("corner1", &camera->corner_upper_left);
	
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_u, 0.5));
	debug_vec3("corner2", &camera->corner_upper_left);
	
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_v, 0.5));
	debug_vec3("corner3", &camera->corner_upper_left);
	
	
	debug_vec3("w", &w);
	debug_vec3("u", &u);
	debug_vec3("v", &v);
	
	return (camera);
}

