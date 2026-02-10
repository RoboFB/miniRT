/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:46 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/10 16:59:21 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

double degrees_to_radians(const double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double linear_to_gamma(const double linear_color_part)
{
	if (linear_color_part > 0)
		return sqrt(linear_color_part);

	return 0;
}