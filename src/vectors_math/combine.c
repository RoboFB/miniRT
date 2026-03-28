/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   combine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:04:46 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	combine_vec3(const t_vec3 a)
{
	return (a.x + a.y + a.z);
}

double	dot_vec3(const t_vec3 a, const t_vec3 b)
{
	return (combine_vec3(mul_vec3(a, b)));
}

double	length_squared_vec3(const t_vec3 a)
{
	return (combine_vec3(square_vec3(a)));
}

double	length_vec3(const t_vec3 a)
{
	return (sqrt(length_squared_vec3(a)));
}
