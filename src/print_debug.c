/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:06:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/27 16:09:05 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_vec3(const char *msg, const t_vec3 *v)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (%f, %f, %f)\n", msg, v->x, v->y, v->z);
}