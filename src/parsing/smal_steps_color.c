/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smal_steps_color.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:08:12 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Parses three 0-255 RGB integers into a t_color_256. */
bool	pars_color_256_converted(const char **line_pos, t_color_256 *result)
{
	if (!pars_int8_in_range_converted(line_pos, &result->r))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_int8_in_range_converted(line_pos, &result->g))
		return (false);
	if (!pars_comma_skipped(line_pos))
		return (false);
	if (!pars_int8_in_range_converted(line_pos, &result->b))
		return (false);
	result->a = 255;
	return (true);
}

/* Parses a 0-255 RGB color and normalizes it to a t_vec3 in [0,1]. */
bool	pars_color_vec3_converted(const char **line_pos, t_vec3 *result_color)
{
	t_color_256	temp_color;

	if (!pars_color_256_converted(line_pos, &temp_color))
		return (false);
	color_256_to_vec3(&temp_color, result_color);
	return (true);
}

/* Parses material properties (type, color, optional fuzz/refraction index). */
bool	pars_material_converted(const char **line_pos,
		t_material *result_material)
{
	result_material->type = MATERIAL_PHONG;
	if (!pars_color_vec3_converted(line_pos, &result_material->color))
		return (false);
	pars_skip_space(line_pos);
	if (ft_strncmp(*line_pos, "mir:", 4) == 0)
	{
		result_material->type = MATERIAL_REFLECTION;
		*line_pos += 4;
		if (!pars_double_in_range_converted(line_pos, &result_material->fuzz,
				(t_interval){0, 1}))
			return (false);
	}
	return (true);
}
