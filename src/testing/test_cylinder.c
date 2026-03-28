/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	test_cy_tube_a(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		result;

	ray = (t_ray){{0, 2, 5}, {0, 0, -1}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!result)
		printf("FAIL - Test 1 tube frontal (expect HIT)\n");
	ray = (t_ray){{5, 2, 0}, {0, 0, 1}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (result)
		printf("FAIL - Test 2 miss beside (expect MISS)\n");
	ray = (t_ray){{5, 2, 0}, {0, 1, 0}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (result)
		printf("FAIL - Test 3 parallel (expect MISS)\n");
}

static void	test_cy_tube_b(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		result;

	ray = (t_ray){{0, 2, 5}, {0, 0, -1}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, 1.0}, &hit);
	if (result)
		printf("FAIL - Test 4 boarder limit (expect MISS)\n");
	ray = (t_ray){{0, 2, 0}, {1, 0, 0}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!result)
		printf("FAIL - Test 5 inside to tube (expect HIT)\n");
}

static void	test_cy_cap_a(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		result;

	ray = (t_ray){{0, 10, 0}, {0, -1, 0}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!result)
		printf("FAIL - Test 6 top cap (expect HIT)\n");
	ray = (t_ray){{0, -5, 0}, {0, 1, 0}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!result)
		printf("FAIL - Test 7 bottom cap (expect HIT)\n");
	ray = (t_ray){{0.5, -5, 0}, {0, 1, 0}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!result)
		printf("FAIL - Test 8 cap off-center (expect HIT)\n");
}

static void	test_cy_cap_b(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_cylinder	cy_tilt;
	bool		result;

	ray = (t_ray){{1.5, -5, 0}, {0, 1, 0}};
	result = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (result)
		printf("FAIL - Test 9 cap outside r (expect MISS)\n");
	cy_tilt = *cy;
	cy_tilt.cylinder.r.direction = normalize_vec3((t_vec3){1, 1, 0});
	cy_tilt.cylinder.r.origin = (t_vec3){0, 0, 5};
	ray = (t_ray){{0, 5, 5}, {0, -1, 0}};
	result = is_hit_cylinder(&cy_tilt, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!result)
		printf("FAIL - Test 10 tilted (expect HIT)\n");
}

void	test_hit_cylinder(void)
{
	t_cylinder	cy;

	ft_bzero(&cy, sizeof(t_cylinder));
	cy.cylinder.r.origin = (t_vec3){0, 2, 0};
	cy.cylinder.r.direction = (t_vec3){0, 1, 0};
	cy.cylinder.length = 4.0;
	cy.radius = 1.0;
	cy.material.type = MATERIAL_PHONG;
	cy.material.color = (t_vec3){0, 1, 0};
	printf("=== test_hit_cylinder ===\n");
	test_cy_tube_a(&cy);
	test_cy_tube_b(&cy);
	test_cy_cap_a(&cy);
	test_cy_cap_b(&cy);
}
