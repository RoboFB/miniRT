/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handers_shapes.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:54:04 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Parses and adds a sphere to the scene (center, radius, material). */
bool	pars_sphere(t_scene *scene, const char **line)
{
	t_sphere	temp_sphere;

	ft_bzero(&temp_sphere, sizeof(t_sphere));
	if (!pars_coordinate_converted(line, &temp_sphere.center))
		return (false);
	if (!pars_double_in_range_converted(line, &temp_sphere.radius,
			(t_interval){0.0, BIG_DOUBLE}))
		return (false);
	temp_sphere.radius *= 0.5;
	if (!pars_material_converted(line, &temp_sphere.material))
		return (false);
	if (dynamic_array_add_back_perror(&scene->spheres, &temp_sphere) == -1)
		return (false);
	return (true);
}

/* Parses and adds a plane to the scene (point, normal, material). */
bool	pars_plane(t_scene *scene, const char **line)
{
	t_plane	temp_plane;

	ft_bzero(&temp_plane, sizeof(t_plane));
	if (!pars_coordinate_converted(line, &temp_plane.plane.origin))
		return (false);
	if (!pars_coordinate_in_range_converted(line,
			&temp_plane.plane.direction, (t_interval){-1.0, 1.0}))
		return (false);
	temp_plane.plane.direction = normalize_vec3(temp_plane.plane.direction);
	if (!pars_material_converted(line, &temp_plane.material))
		return (false);
	if (dynamic_array_add_back_perror(&scene->planes, &temp_plane) == -1)
		return (false);
	return (true);
}

/* Parses and adds a cylinder to the scene (center, axis, radius, height). */
bool	pars_cylinder(t_scene *scene, const char **line)
{
	t_cylinder	temp_cylinder;

	ft_bzero(&temp_cylinder, sizeof(t_cylinder));
	if (!pars_coordinate_converted(line, &temp_cylinder.cylinder.r.origin))
		return (false);
	if (!pars_coordinate_in_range_converted(line,
			&temp_cylinder.cylinder.r.direction, (t_interval){-1.0, 1.0}))
		return (false);
	temp_cylinder.cylinder.r.direction = normalize_vec3(
			temp_cylinder.cylinder.r.direction);
	if (!pars_double_in_range_converted(line, &temp_cylinder.radius,
			(t_interval){0.0, BIG_DOUBLE}))
		return (false);
	temp_cylinder.radius *= 0.5;
	if (!pars_atof_converted(line, &temp_cylinder.cylinder.length))
		return (false);
	if (!pars_material_converted(line, &temp_cylinder.material))
		return (false);
	if (dynamic_array_add_back_perror(&scene->cylinders, &temp_cylinder) == -1)
		return (false);
	return (true);
}
