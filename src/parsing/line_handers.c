/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_handers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 14:54:04 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/31 12:56:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Parses and sets scene ambient light (intensity and color). */
bool	pars_ambient_light(t_scene *scene, const char **line)
{
	if (scene->ambient_light->already_parsed)
		return (false);
	scene->ambient_light->already_parsed = true;
	if (!pars_double_in_range_converted(line, &scene->ambient_light->ratio,
			(t_interval){0.0, 1.0}))
		return (false);
	if (!pars_color_vec3_converted(line, &scene->ambient_light->color))
		return (false);
	return (true);
}

/* Parses and sets scene camera (position, direction, FOV). */
bool	pars_camera(t_scene *scene, const char **line)
{
	if (scene->camera->already_parsed)
		return (false);
	scene->camera->already_parsed = true;
	if (!pars_coordinate_converted(line, &scene->camera->ray.r.origin))
		return (false);
	if (!pars_coordinate_in_range_converted(line,
			&scene->camera->ray.r.direction, (t_interval){-1.0, 1.0}))
		return (false);
	if (!pars_double_in_range_converted(line, &scene->camera->fov,
			(t_interval){0.0, 180.0}))
		return (false);
	scene->camera->ray.r.direction = normalize_vec3(
			scene->camera->ray.r.direction);
	return (true);
}

/* Parses and adds a point light to the scene (position, intensity, color). */
bool	pars_light(t_scene *scene, const char **line)
{
	t_light	temp_light;

	ft_bzero(&temp_light, sizeof(t_light));
	if (!pars_coordinate_converted(line, &temp_light.position))
		return (false);
	if (!pars_double_in_range_converted(line, &temp_light.ratio,
			(t_interval){0.0, 1.0}))
		return (false);
	if (!pars_color_vec3_converted(line, &temp_light.color))
		return (false);
	if (dynamic_array_add_back_perror(&scene->lights, &temp_light) == -1)
		return (false);
	return (true);
}
