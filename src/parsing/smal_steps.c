/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smal_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:08:12 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/06 15:01:09 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// R; true = success, error = false
bool pars_coordinate_converted(const char **line_pos, t_vec3 *result)
{
	if (!pars_atof_converted(line_pos, &result->x))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_atof_converted(line_pos, &result->y))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_atof_converted(line_pos, &result->z))
		return (false);
	return (true);
}

// R; true = success, error = false
bool pars_coordinate_in_range_converted(const char **line_pos, t_vec3 *result, t_interval range)
{
	if (!pars_double_in_range_converted(line_pos, &result->x, range))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_double_in_range_converted(line_pos, &result->y, range))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_double_in_range_converted(line_pos, &result->z, range))
		return (false);
	return (true);
}

// R; true = success, error = false
bool pars_double_in_range_converted(const char **line_pos, double *result, t_interval range)
{
	if (!pars_atof_converted(line_pos, result))
		return (false);
	
	if (!is_interval_in(range, *result))
		return (false);
	
	return (true);
}

// R; true = success, error = false
bool pars_int8_in_range_converted(const char **line_pos, uint8_t *result)
{
	int tmp;
	if (!pars_atoi_converted(line_pos, &tmp))
		return (false);
	
	if (tmp < 0 || tmp > 255)
		return (false);
	*result = tmp;
	return (true);
}

// R; true = success, error = false
bool pars_color_256_converted(const char **line_pos, t_color_256 *result_color)
{
	if (!pars_int8_in_range_converted(line_pos, &result_color->r))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_int8_in_range_converted(line_pos, &result_color->g))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_int8_in_range_converted(line_pos, &result_color->b))
		return (false);
	result_color->a = 255; // default alpha to fully opaque
	return (true);
}

// R; true = success, error = false
bool pars_color_vec3_converted(const char **line_pos, t_vec3 *result_color)
{
	t_color_256 temp_color;

	if (!pars_color_256_converted(line_pos, &temp_color))
		return (false);
	color_256_to_vec3(&temp_color, result_color);
	return (true);
}

// R; true = success, error = false
bool pars_material_converted(const char **line_pos, t_material *result_material)
{
	result_material->type = MATERIAL_PHONG;
	
	if (!pars_color_vec3_converted(line_pos, &result_material->color))
		return (false);
	pars_skip_space(line_pos);
	if (ft_strncmp(*line_pos, "mir:", 4) == 0)
	{
		result_material->type = MATERIAL_REFLECTION;
		*line_pos += 4;
		if (!pars_double_in_range_converted(line_pos, &result_material->fuzz, (t_interval){0, 1}))
			return (false);
	}
	return (true);
}