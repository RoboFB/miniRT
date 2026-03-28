/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	add_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
}

void	sub_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x -= b.x;
	a->y -= b.y;
	a->z -= b.z;
}

void	mul_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x *= b.x;
	a->y *= b.y;
	a->z *= b.z;
}

void	div_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x /= b.x;
	a->y /= b.y;
	a->z /= b.z;
}
