/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinder.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/28 00:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Test setup used by all cases:
// Upright cylinder, center=(0,2,0), axis=(0,1,0), radius=1, height=4.
// Bottom cap at y=0, top cap at y=4.
static t_cylinder	make_test_cylinder(void)
{
	t_cylinder	cy;

	ft_bzero(&cy, sizeof(t_cylinder));
	cy.cylinder.r.origin = (t_vec3){0, 2, 0};
	cy.cylinder.r.direction = (t_vec3){0, 1, 0};
	cy.cylinder.length = 4.0;
	cy.radius = 1.0;
	cy.material.type = MATERIAL_PHONG;
	cy.material.color = (t_vec3){0, 1, 0};
	return (cy);
}

// Tests 1-5: tube hits, misses, and parallel rays.
static void	test_cylinder_tube_cases(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;
	bool		result;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 2, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 1 - tube frontal:    %s (expect HIT)\n", result ? "HIT" : "MISS");
	ray = (t_ray){{5, 2, 0}, {0, 0, 1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 2 - miss beside:     %s (expect MISS)\n", result ? "HIT" : "MISS");
	ray = (t_ray){{5, 2, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 3 - parallel beside: %s (expect MISS)\n", result ? "HIT" : "MISS");
	ray = (t_ray){{0, 2, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, (t_interval){SMALL_DOUBLE, 1.0}, &hit);
	printf("Test 4 - boarder limit:   %s (expect MISS)\n", result ? "HIT" : "MISS");
	ray = (t_ray){{0, 2, 0}, {1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 5 - inside to tube:  %s (expect HIT)\n", result ? "HIT" : "MISS");
}

// Tests 6-10: cap hits, edge cases, and tilted cylinder.
static void	test_cylinder_cap_cases(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;
	t_cylinder	cy_tilt;
	bool		result;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 10, 0}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 6 - top cap:         %s (expect HIT)\n", result ? "HIT" : "MISS");
	if (result)
		debug_vec3("  normal", &hit.r.direction);
	ray = (t_ray){{0, -5, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 7 - bottom cap:      %s (expect HIT)\n", result ? "HIT" : "MISS");
	if (result)
		debug_vec3("  normal", &hit.r.direction);
	ray = (t_ray){{0.5, -5, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 8 - cap off-center:  %s (expect HIT)\n", result ? "HIT" : "MISS");
	ray = (t_ray){{1.5, -5, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Test 9 - cap outside r:   %s (expect MISS)\n", result ? "HIT" : "MISS");
	cy_tilt = *cy;
	cy_tilt.cylinder.r.direction = normalize_vec3((t_vec3){1, 1, 0});
	cy_tilt.cylinder.r.origin = (t_vec3){0, 0, 5};
	ray = (t_ray){{0, 5, 5}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_cylinder(&cy_tilt, &ray, b, &hit);
	printf("Test 10 - tilted cylinder:%s (expect HIT)\n", result ? "HIT" : "MISS");
}

// Runs all 10 cylinder intersection unit tests.
// Setup: upright cylinder center=(0,2,0), axis=(0,1,0), radius=1, height=4.
void	test_hit_cylinder(void)
{
	t_cylinder	cy;

	cy = make_test_cylinder();
	printf("=== test_hit_cylinder ===\n");
	test_cylinder_tube_cases(&cy);
	test_cylinder_cap_cases(&cy);
}
