/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:04:03 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 18:05:03 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a > b uses length squared to compare
bool	is_bigger_vec3(const t_vec3 val, const t_vec3 against)
{
	return (length_squared_vec3(val) > length_squared_vec3(against));
}

// is in or on the each (min <= x <= max)
bool	is_interval_in_vec3(const t_vec3 value, const t_vec3 min, const t_vec3 max)
{
	if (is_bigger_vec3(value, max))
		return (false);
	if (is_bigger_vec3(min, value))
		return (false);
	else
		return (true);
}


// if in +-0.0001
bool	near_zero(const double value)
{
	return (value > -0.0001 && value < 0.0001);
}

// all x,y,z are near zero
bool	vec3_is_near_zero(const t_vec3 a)
{
	return (near_zero(a.x) && near_zero(a.y) && near_zero(a.z));
}




