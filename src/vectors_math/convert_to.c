/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:46 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	degrees_to_radians(const double degrees)
{
	return (degrees * (M_PI / 180.0));
}

double	linear_to_gamma(const double linear_color_part)
{
	if (linear_color_part > 0)
		return (sqrt(linear_color_part));
	return (0);
}

void	color_256_to_vec3(t_color_256 *in, t_vec3 *out)
{
	out->x = (double)in->r / 255.0;
	out->y = (double)in->g / 255.0;
	out->z = (double)in->b / 255.0;
}
