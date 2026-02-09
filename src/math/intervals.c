/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:18:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 18:04:19 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


// double	interval_size(t_interval interval)
// {
// 	return (interval.max - interval.min);
// }

// is in or on the each (min <= x <= max)
bool	is_interval_in(const t_interval interval, const double value)
{
	// if (value >= interval.min && value <= interval.max)
	return (value >= interval.min && value <= interval.max);
}
// double	interval_is_outside(t_interval interval, double value)
// {
// 	return (value < interval.min || value > interval.max);
// }
