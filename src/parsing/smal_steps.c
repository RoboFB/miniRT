/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   smal_steps.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:08:12 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:11:11 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Parses three comma-separated doubles as a t_vec3 coordinate. */
bool	pars_coordinate_converted(const char **line_pos, t_vec3 *result)
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

/* Parses a t_vec3 coordinate and validates each component against the range. */
bool	pars_coordinate_in_range_converted(const char **line_pos,
		t_vec3 *result, t_interval range)
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

/* Parses a double and validates it against the given interval. */
bool	pars_double_in_range_converted(const char **line_pos, double *result,
		t_interval range)
{
	if (!pars_atof_converted(line_pos, result))
		return (false);
	if (!is_interval_in(range, *result))
		return (false);
	return (true);
}

/* Parses an integer in [0,255] and stores it as uint8_t. */
bool	pars_int8_in_range_converted(const char **line_pos, uint8_t *result)
{
	int	tmp;

	if (!pars_atoi_converted(line_pos, &tmp))
		return (false);
	if (tmp < 0 || tmp > 255)
		return (false);
	*result = tmp;
	return (true);
}
