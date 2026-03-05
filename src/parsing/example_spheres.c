/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_spheres.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:58:29 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/03 18:09:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	example_purple_spheres(t_dynamic_array *spheres)
{
	dynamic_array_add_back_exit(spheres, &(t_sphere){ // left
		.center = (t_vec3){-0.5, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.1, 0.000001, 0.1},
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){ // ground
		.center = (t_vec3){0.0, -100.5, -1.0},
		.radius = 100.0,
		.material = (t_material){
			.type = MATERIAL_REFLECTION,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.fuzz = 0.01,
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){ // in 0.4r 1.5
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.4,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.0/1.5,
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){ // out 0.5r 1.0
		.center = (t_vec3){0.5, 0.2, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.color = (t_vec3){0.7, 0.7, 0.7},
			.refraction_index = 1.0,
		},
	});
}

void example_first_spheres(t_dynamic_array *spheres)
{
	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){0.0, -100.5, -1.0},
		.radius = 100.0,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.8, 0.8, 0.0},
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){0.0, 0.0, -1.2},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.1, 0.2, 0.5},
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){-1.0, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.refraction_index = 1.50,
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){-1.0, 0.0, -1.0},
		.radius = 0.4,
		.material = (t_material){
			.type = MATERIAL_DIELECTRIC,
			.refraction_index = 1.0 / 1.50,
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){1.0, 0.0, -1.0},
		.radius = 0.5,
		.material = (t_material){
			.type = MATERIAL_REFLECTION,
			.color = (t_vec3){0.8, 0.6, 0.2},
			.fuzz = 1,
		},
	});
}


void example_fov_spheres(t_dynamic_array *spheres)
{
	double radius = cos(M_PI/4.0);

	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){-radius, 0.0, -1.0},
		.radius = radius,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){0.0, 0.0, 1.0},
		},
	});
	dynamic_array_add_back_exit(spheres, &(t_sphere){
		.center = (t_vec3){radius, 0.0, -1.0},
		.radius = radius,
		.material = (t_material){
			.type = MATERIAL_LAMBERTIAN,
			.color = (t_vec3){1.0, 0.0, 0.0},
		},
	});
}
