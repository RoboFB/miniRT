/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing_main.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 09:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/28 12:09:59 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int	dispatch_basic(const char *name)
{
	if (ft_strncmp(name, "dynamic_array", 15) == 0)
	{
		test_dynamic_array();
		return (1);
	}
	if (ft_strncmp(name, "random", 7) == 0)
	{
		test_random();
		return (1);
	}
	if (ft_strncmp(name, "r3", 3) == 0)
	{
		test_r3();
		return (1);
	}
	return (0);
}

static int	dispatch_shapes(const char *name)
{
	if (ft_strncmp(name, "hit_plane", 10) == 0)
	{
		test_hit_plane();
		return (1);
	}
	if (ft_strncmp(name, "hit_cylinder", 13) == 0)
	{
		test_hit_cylinder();
		test_hit_cylinder_ext();
		return (1);
	}
	return (0);
}

int	test_caller(int argc, char const *argv[])
{
	if (DEBUG_RT == 0 || argc != 3)
		return (0);
	if (ft_strncmp(argv[1], "-t", 3) != 0
		&& ft_strncmp(argv[1], "--test", 7) != 0)
		return (0);
	if (dispatch_basic(argv[2]))
		return (1);
	return (dispatch_shapes(argv[2]));
}
