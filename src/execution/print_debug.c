/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:06:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/13 13:38:23 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	debug_vec3(const char *msg, const t_vec3 *v)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (x%f, y%f, z%f)\n", msg, v->x, v->y, v->z);
}

void	debug_ray(const char *msg, const t_ray *ray)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: origin: (%.3f, %.3f, %.3f)   direction: (%.3f ,%.3f ,%.3f)\n", 
		msg, 
		ray->origin.x, ray->origin.y, ray->origin.z, 
		ray->direction.x, ray->direction.y, ray->direction.z);
}

void	debug_decimal(const char *msg, double d)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (%.3f)\n", msg, d);
}
