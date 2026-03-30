/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intervals.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 14:18:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/30 12:38:29 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// is in or on the each (min <= x <= max)
bool	is_interval_in(const t_interval interval, const double value)
{
	return (value >= interval.min && value <= interval.max);
}
