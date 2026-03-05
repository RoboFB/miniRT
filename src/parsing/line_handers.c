/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:54:04 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/04 19:14:50 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool pars_ambient_light(t_scene *scene, const char **line)
{
	static bool already_parsed = false;
	const static t_interval range_ration = {0.0, 1.0};
	
	if (already_parsed)
		return (false);
	already_parsed = true;
	
	if (!pars_double_in_range_converted(line, &scene->ambient_light->ratio, range_ration))
		return (false);
	if (!pars_color_vec3_converted(line, &scene->ambient_light->color))
		return (false);
	return (true);
}

bool pars_camera(t_scene *scene, const char **line)
{
	static bool already_parsed = false;
	const static t_interval range_fov = {0.0, 180.0};
	const static t_interval range_direction = {-1.0, 1.0};

	if (already_parsed)
		return (false);
	already_parsed = true;
	if (!pars_coordinate_converted(line, &scene->camera->ray.r.origin))
		return (false);
	if (!pars_coordinate_in_range_converted(line, &scene->camera->ray.r.direction, range_direction))
		return (false);
	if (!pars_double_in_range_converted(line, &scene->camera->fov, range_fov))
		return (false);
	return (true);

}

bool pars_light(t_scene *scene, const char **line)
{
	t_light temp_light = {0};
	const static t_interval range_ration = {0.0, 1.0};

	if (!pars_coordinate_converted(line, &temp_light.position))
		return (false);
	if (!pars_double_in_range_converted(line, &temp_light.ratio, range_ration))
		return (false);
	if (!pars_color_vec3_converted(line, &temp_light.color))
		return (false);
	if (dynamic_array_add_back_perror(&scene->lights, &temp_light) == -1)
		return (false);
	return (true);
}

bool pars_sphere(t_scene *scene, const char **line)
{
	t_sphere temp_sphere = {0};
	const static t_interval range_diameter = {0.0, BIG_DOUBLE};
	
	if (!pars_coordinate_converted(line, &temp_sphere.center))
		return (false);
	if (!pars_double_in_range_converted(line, &temp_sphere.radius, range_diameter))
		return (false);
	temp_sphere.radius *= 0.5; // convert diameter to radius
	if (!pars_material_converted(line, &temp_sphere.material))
		return (false);
	if (dynamic_array_add_back_perror(&scene->spheres, &temp_sphere) == -1)
		return (false);
	return (true);
}

bool pars_plane(t_scene *scene, const char **line)
{
	t_plane temp_plane = {0};
	const static t_interval range_direction = {-1.0, 1.0};
	
	if (!pars_coordinate_converted(line, &temp_plane.plane.origin))
		return (false);
	if (!pars_coordinate_in_range_converted(line, &temp_plane.plane.direction, range_direction))
		return (false);
	if (!pars_material_converted(line, &temp_plane.material))
		return (false);
	if (dynamic_array_add_back_perror(&scene->planes, &temp_plane) == -1)
		return (false);
	return (true);
}

bool pars_cylinder(t_scene *scene, const char **line)
{
	t_cylinder temp_cylinder = {0};
	const static t_interval range_direction = {-1.0, 1.0};
	const static t_interval range_diameter = {0.0, BIG_DOUBLE};
	

	if (!pars_coordinate_converted(line, &temp_cylinder.cylinder.r.origin))
		return (false);
	if (!pars_coordinate_in_range_converted(line, &temp_cylinder.cylinder.r.direction, range_direction))
		return (false);

	if (!pars_double_in_range_converted(line, &temp_cylinder.radius, range_diameter))
		return (false);
	temp_cylinder.radius *= 0.5; // convert diameter to radius

	if (!pars_atof_converted(line, &temp_cylinder.cylinder.length))
		return (false);

	if (!pars_material_converted(line, &temp_cylinder.material))
		return (false);
	if (dynamic_array_add_back_perror(&scene->cylinders, &temp_cylinder) == -1)
		return (false);
	return (true);
}
