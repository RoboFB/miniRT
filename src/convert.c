/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 16:41:17 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/28 16:52:13 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_color_d vec3_to_color_d(const t_vec3 v)
{
	t_color_d color;

	color.r = v.x;
	color.g = v.y;
	color.b = v.z;
	return (color);
}
