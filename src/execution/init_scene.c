/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_scene.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:56:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:13:03 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Allocates and zeroes all scene dynamic arrays; exits on failure. */
void	init_scene_exit(t_scene *scene)
{
	scene->camera = calloc_perror_exit(1, sizeof(t_camera));
	scene->ambient_light = calloc_perror_exit(1, sizeof(t_ambient_light));
	scene->lights = dynamic_array_init_exit(sizeof(t_light));
	scene->spheres = dynamic_array_init_exit(sizeof(t_sphere));
	scene->planes = dynamic_array_init_exit(sizeof(t_plane));
	scene->cylinders = dynamic_array_init_exit(sizeof(t_cylinder));
}

/* Computes camera orthonormal basis vectors (u right, v up). */
static void	calc_basis_vectors(t_camera *cam, t_vec3 *u, t_vec3 *v)
{
	t_vec3	vup;
	t_vec3	w;

	vup = (t_vec3){0.0, 1.0, 0.0};
	w = cam->ray.r.direction;
	if (fabs(dot_vec3(vup, w)) > 0.999)
		vup = (t_vec3){0.0, 0.0, 1.0};
	*u = normalize_vec3(cross_vec3(w, vup));
	*v = cross_vec3(w, *u);
}

/* Computes pixel-step vectors for the viewport from image and camera data. */
static void	calc_viewport(mlx_image_t *img, t_camera *cam,
		t_vec3 *viewport_u, t_vec3 *viewport_v)
{
	t_vec3	u;
	t_vec3	v;
	double	scale;
	double	vp_height;

	scale = tan(degrees_to_radians(cam->fov) * 0.5);
	vp_height = 2.0 * scale * cam->ray.length;
	calc_basis_vectors(cam, &u, &v);
	*viewport_u = mul_one_vec3(u,
			vp_height * ((double)img->width / (double)img->height));
	*viewport_v = mul_one_vec3(v, vp_height);
}

/* Prints camera parameters to stdout when DEBUG_RT is enabled. */
static void	debug_camera(const t_camera *camera)
{
	if (DEBUG_RT == 0)
		return ;
	debug_vec3("camera origin   ", &camera->ray.r.origin);
	debug_vec3("camera direction", &camera->ray.r.direction);
	debug_vec3("delta_u         ", &camera->delta_u);
	debug_vec3("delta_v         ", &camera->delta_v);
	debug_vec3("corner_upper_left", &camera->corner_upper_left);
}

/* Computes all camera geometry (basis, viewport, pixel deltas). */
void	calculate_camera(mlx_image_t *img, t_camera *camera)
{
	t_vec3	viewport_u;
	t_vec3	viewport_v;

	camera->ray.length = 1.0;
	camera->max_deep_rays = 16;
	camera->anti_aliasing_samples = 32;
	calc_viewport(img, camera, &viewport_u, &viewport_v);
	camera->delta_u = div_one_vec3(viewport_u, (double)(img->width));
	camera->delta_v = div_one_vec3(viewport_v, (double)(img->height));
	camera->corner_upper_left = add_vec3(camera->ray.r.origin,
			mul_one_vec3(camera->ray.r.direction, camera->ray.length));
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_u, -0.5));
	add_vec3_p(&camera->corner_upper_left, mul_one_vec3(viewport_v, -0.5));
	debug_camera(camera);
}
