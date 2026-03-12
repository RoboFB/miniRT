/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:56:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/12 12:01:38 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

void init_scene_exit(t_scene *scene)
{
	scene->camera = calloc_perror_exit(1, sizeof(t_camera));
	scene->ambient_light = calloc_perror_exit(1, sizeof(t_ambient_light));

	scene->lights = dynamic_array_init_exit(sizeof(t_light));
	scene->spheres = dynamic_array_init_exit(sizeof(t_sphere));
	scene->planes = dynamic_array_init_exit(sizeof(t_plane));
	scene->cylinders = dynamic_array_init_exit(sizeof(t_cylinder));
	return ;
}





void calculate_camera(mlx_image_t *img, t_camera *camera)
{
	camera->ray.length = 1.0; // focal length
	camera->max_deep_rays = 16;
	camera->anti_aliasing_samples = 32; // no *2 in main hock

	
	double scale = tan(degrees_to_radians(camera->fov) * 0.5);
	
	double viewport_height = 2.0 * scale * camera->ray.length;
	double imageAspectRatio = (double)img->width / (double)img->height;
	double viewport_width = viewport_height * imageAspectRatio;
	

	// Calculate the u,v,w unit basis vectors for the camera coordinate frame.
	t_vec3 vup = (t_vec3){0.0, 1.0, 0.0}; // relative up for changeing angels later if needed and for the caluactions needed i think

	
	t_vec3 w = camera->ray.r.direction; //richtung tife ist schon normalized
	if (fabs(dot_vec3(vup, w)) > 0.999)
        vup = (t_vec3){0.0, 0.0, 1.0};
	t_vec3 u = normalize_vec3(cross_vec3(w,vup)); // richtung breite
	t_vec3 v = cross_vec3(w, u); // richtung hohe

	t_vec3 viewport_u = mul_one_vec3(u, viewport_width);
	t_vec3 viewport_v = mul_one_vec3(v, viewport_height);

	camera->delta_u = div_one_vec3(viewport_u, (double)(img->width));
	camera->delta_v = div_one_vec3(viewport_v, (double)(img->height));
	
	// Start at focal point (in front of camera), then move to upper-left corner
	camera->corner_upper_left = add_vec3(camera->ray.r.origin, mul_one_vec3(w, camera->ray.length));
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_u, -0.5));
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_v, -0.5));
	
	


	debug_vec3("camera origin", &camera->ray.r.origin);
	debug_vec3("camera direction", &camera->ray.r.direction);
    debug_vec3("camera direction (w)", &w);
    debug_vec3("camera right (u)", &u);
    debug_vec3("camera up (v)", &v);
	puts("");
    debug_vec3("viewport_u", &viewport_u);
    debug_vec3("delta_u   ", &camera->delta_u);
    debug_vec3("viewport_v", &viewport_v);
    debug_vec3("delta_v   ", &camera->delta_v);
	puts("");
	
    debug_vec3("corner_upper_left", &camera->corner_upper_left);

	debug_decimal("w length (should be 1.0)", length_vec3(w));
	debug_decimal("u length (should be 1.0)", length_vec3(u));
	debug_decimal("v length (should be 1.0)", length_vec3(v));
	// Check orthogonality:
	debug_decimal("u·v (should be ~0)", dot_vec3(u, v));
	debug_decimal("u·w (should be ~0)", dot_vec3(u, w));
	
	return ;
}

