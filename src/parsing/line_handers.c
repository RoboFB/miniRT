/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:54:04 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/18 15:58:31 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool pars_ambient_light(t_scene *scene, const char **line)
{
	(void)scene;
	(void)line;
	return (true);

}

bool pars_camera(t_scene *scene, const char **line)
{
	t_interval range_fov = {0.0, 180.0};
	t_interval range_direction = {-1.0, 1.0};

	if (!pars_coordinate_converted(line, &scene->camera->ray.r.origin))
		return (false);
	if (!pars_coordinate_interval_converted(line, &scene->camera->ray.r.direction, range_direction))
		return (false);
	if (!pars_double_in_range_converted(line, &scene->camera->fov, range_fov))
		return (false);
	return (true);

}

bool pars_light(t_scene *scene, const char **line)
{
	(void)scene;
	(void)line;
	return (true);

}

bool pars_sphere(t_scene *scene, const char **line)
{
	t_sphere temp_sphere = {0};
	
	temp_sphere.material.type = MATERIAL_LAMBERTIAN; // set as default,
	
	if (!pars_coordinate_converted(line, &temp_sphere.center))
		return (false);
	if (!pars_atof_converted(line, &temp_sphere.radius))
		return (false);
	if (!pars_color_vec3_converted(line, &temp_sphere.material.color))
		return (false);
	debug_sphere(&temp_sphere);
	dynamic_array_add_back(&scene->spheres, &temp_sphere);
	
	return (true);
}

bool pars_plane(t_scene *scene, const char **line)
{
	(void)scene;
	(void)line;
	return (true);

}

bool pars_cylinder(t_scene *scene, const char **line)
{
	(void)scene;
	(void)line;
	return (true);

}
