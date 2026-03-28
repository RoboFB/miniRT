/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinder_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:10:22 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	test_cy_tube_normals(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 2, 5}, {0, 0, -1}};
	is_hit_cylinder(cy, &ray, b, &hit);
	printf("Normal from +z:  expect (0, 0, 1)\n");
	debug_vec3("  actual", &hit.r.direction);
	ray = (t_ray){{5, 2, 0}, {-1, 0, 0}};
	is_hit_cylinder(cy, &ray, b, &hit);
	printf("Normal from +x:  expect (1, 0, 0)\n");
	debug_vec3("  actual", &hit.r.direction);
	ray = (t_ray){{5, 2, 5}, {-1, 0, -1}};
	is_hit_cylinder(cy, &ray, b, &hit);
	printf("Normal from xz:  expect (0.707, 0, 0.707)\n");
	debug_vec3("  actual", &hit.r.direction);
}

static void	test_cy_height_bounds(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		r;

	ray = (t_ray){{0, 0, 5}, {0, 0, -1}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!r)
		printf("FAIL - Height m=0 bottom edge (expect HIT)\n");
	ray = (t_ray){{0, 4, 5}, {0, 0, -1}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!r)
		printf("FAIL - Height m=h top edge (expect HIT)\n");
	ray = (t_ray){{0, 4.5, 5}, {0, 0, -1}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (r)
		printf("FAIL - Height m>h above top (expect MISS)\n");
	ray = (t_ray){{0, -0.5, 5}, {0, 0, -1}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (r)
		printf("FAIL - Height m<0 below bottom (expect MISS)\n");
}

static void	test_cy_surface_order(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;
	bool		r;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 5, 0.3}, {0, -1, -0.3}};
	r = is_hit_cylinder(cy, &ray, b, &hit);
	if (!r)
		printf("FAIL - cap closer than tube (expect HIT)\n");
	if (r)
		printf("  y=%.1f (expect 4.0=top cap)\n", hit.r.origin.y);
	ray = (t_ray){{2, 2, 0}, {-1, 0, 0}};
	r = is_hit_cylinder(cy, &ray, b, &hit);
	if (!r)
		printf("FAIL - tube wins no cap (expect HIT)\n");
	if (r)
		printf("  x=%.1f (expect 1.0=tube)\n", hit.r.origin.x);
}

static void	test_cy_inside_and_self(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		r;

	ray = (t_ray){{0, 2, 0}, {1, 0, 0}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!r)
		printf("FAIL - inside to tube (expect HIT)\n");
	ray = (t_ray){{0, 2, 0}, {0, 1, 0}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (!r)
		printf("FAIL - inside to top cap (expect HIT)\n");
	ray = (t_ray){{1, 2, 0}, {1, 0, 0}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (r)
		printf("FAIL - self-intersect tube (expect MISS)\n");
	ray = (t_ray){{0, 4, 0}, {0, 1, 0}};
	r = is_hit_cylinder(cy, &ray,
			(t_interval){SMALL_DOUBLE, BIG_DOUBLE}, &hit);
	if (r)
		printf("FAIL - self-intersect cap (expect MISS)\n");
}

void	test_hit_cylinder_ext(void)
{
	t_cylinder	cy;

	ft_bzero(&cy, sizeof(t_cylinder));
	cy.cylinder.r.origin = (t_vec3){0, 2, 0};
	cy.cylinder.r.direction = (t_vec3){0, 1, 0};
	cy.cylinder.length = 4.0;
	cy.radius = 1.0;
	printf("=== test_hit_cylinder_ext ===\n");
	printf("--- tube normals ---\n");
	test_cy_tube_normals(&cy);
	printf("--- height bounds ---\n");
	test_cy_height_bounds(&cy);
	printf("--- surface order ---\n");
	test_cy_surface_order(&cy);
	printf("--- inside & self-intersection ---\n");
	test_cy_inside_and_self(&cy);
}
