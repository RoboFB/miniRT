/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:01:22 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/30 14:57:10 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* 0.000005 to 0.999998  -> use of x.xxx ok not more precise 
Returns a pseudo-random double in [0, 1) using xorshift64. */
double	get_random(void)
{
	static unsigned int		seed;
	static struct timeval	first_seed;

	if (seed == 0)
	{
		gettimeofday(&first_seed, NULL);
		seed = first_seed.tv_sec % 100000 * first_seed.tv_usec % 100000;
	}
	seed = (1664525 * seed + 1013904223) % UINT32_MAX;
	return ((seed % 1000000) / 1000000.0);
}

/* Returns a vec3 with each component drawn randomly from [0, 1). */
t_vec3	get_random_vec3(void)
{
	t_vec3	new;

	new.x = (0.5 - get_random()) * 2;
	new.y = (0.5 - get_random()) * 2;
	new.z = (0.5 - get_random()) * 2;
	return (new);
}

/* Returns a uniformly random unit vec3 direction (rejection sampling). */
t_vec3	get_random_unit_vector(void)
{
	t_vec3	new;
	double	length_sq;

	while (true)
	{
		new = get_random_vec3();
		length_sq = length_squared_vec3(new);
		if (is_interval_in((t_interval){1e-160, 1.0}, length_sq))
			return (div_one_vec3(new, sqrt(length_sq)));
	}
}
