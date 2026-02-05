/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   radians.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:05:46 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/05 11:18:14 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

double degrees_to_radians(const double degrees)
{
	return (degrees * (M_PI / 180.0));
}
