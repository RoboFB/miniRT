/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:04:03 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/30 12:40:31 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a > b uses length squared to compare
bool	is_bigger_vec3(const t_vec3 val, const t_vec3 against)
{
	return (length_squared_vec3(val) > length_squared_vec3(against));
}

// is in or on the each (min <= x <= max)
bool	is_interval_in_vec3(const t_vec3 value, const t_vec3 min,
		const t_vec3 max)
{
	if (is_bigger_vec3(value, max))
		return (false);
	if (is_bigger_vec3(min, value))
		return (false);
	return (true);
}

// if in +- SMALL_DOUBLE
bool	is_near_zero(const double value)
{
	return (value > -SMALL_DOUBLE && value < SMALL_DOUBLE);
}

// all x,y,z are near zero
bool	is_near_zero_vec3(const t_vec3 a)
{
	return (is_near_zero(a.x) && is_near_zero(a.y) && is_near_zero(a.z));
}
