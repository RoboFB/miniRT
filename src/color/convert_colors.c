/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:17 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/06 12:46:32 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double linear_to_gamma(const double linear_color_part)
{
	if (linear_color_part > 0)
		return sqrt(linear_color_part);

	return 0;
}
