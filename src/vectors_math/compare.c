/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:04:03 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:08:36 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	is_bigger_vec3(const t_vec3 val, const t_vec3 against)
{
	return (length_squared_vec3(val) > length_squared_vec3(against));
}

bool	is_interval_in_vec3(const t_vec3 value, const t_vec3 min,
		const t_vec3 max)
{
	if (is_bigger_vec3(value, max))
		return (false);
	if (is_bigger_vec3(min, value))
		return (false);
	return (true);
}

bool	is_near_zero(const double value)
{
	return (value > -SMALL_DOUBLE && value < SMALL_DOUBLE);
}

bool	is_near_zero_vec3(const t_vec3 a)
{
	return (is_near_zero(a.x) && is_near_zero(a.y) && is_near_zero(a.z));
}
