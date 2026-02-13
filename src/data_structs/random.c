/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 16:01:22 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/12 12:14:30 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


/* 
easy but not very good random generator 
0.0000 to 0.9999 (0 <= x < 1.0)
 */
// double get_random()
// { 
// 	static struct timeval	tv;

// 	gettimeofday((struct timeval *)&tv, NULL);

// 	return ((double)(tv.tv_usec%10000)/10000.0);
// }


/* 
better but still todo: make it great
0.000005 to 0.999998  -> use of x.xxx ok not more precise
*/
double get_random()
{
	static unsigned int				seed = {0};
	static struct timeval	first_seed = {0};
	const unsigned int				a = 1664525;
	const unsigned int				c = 1013904223;
	const unsigned int				m = UINT32_MAX; // 2^32

	if (seed == 0)
	{
		gettimeofday(&first_seed, NULL);
		seed = first_seed.tv_sec%100000 * first_seed.tv_usec%100000;
	}
	seed = (a * seed + c) % m;
	return ((seed % 1000000) / 1000000.0);
}

// x,y,z -> -0.999998 to 0.999998
t_vec3 get_random_vec3()
{
	t_vec3 new;

	new.x = (0.5 - get_random()) * 2;
	new.y = (0.5 - get_random()) * 2;
	new.z = (0.5 - get_random()) * 2;
	return (new);
}

t_vec3 get_random_unit_vector()
{
	t_vec3 new;

	while (true)
	{
		new = get_random_vec3();
		double length_squared = length_squared_vec3(new);
		if (is_interval_in((t_interval){1e-160, 1.0}, length_squared))
			return (div_one_vec3(new , sqrt(length_squared)));
	}
}
