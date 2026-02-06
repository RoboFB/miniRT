/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/06 13:04:03 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/06 13:11:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// a > b uses length squared to compare
bool	vec3_is_bigger(const t_vec3 val, const t_vec3 against)
{
	return (vec3_length_squared(val) > vec3_length_squared(against));
}

// is in or on the each (min <= x <= max)
bool	vec3_interval_is_in(const t_vec3 value, const t_vec3 min, const t_vec3 max)
{
	if (vec3_is_bigger(value, max))
		return (false);
	if (vec3_is_bigger(min, value))
		return (false);
	else
		return (true);
}