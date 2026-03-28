/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cylinder_ext.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42heilbronn.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 00:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/28 00:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// Verifies that tube normals point in the correct radial direction.
// Wrong normals cause broken lighting even if hit detection is correct.
// Cylinder: center=(0,2,0), axis=(0,1,0), r=1, h=4. Bottom at y=0.
static void	test_cy_tube_normals(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 2, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	is_hit_cylinder(cy, &ray, b, &hit);
	printf("Normal from +z:  expect (0, 0, 1)\n");
	debug_vec3("  actual", &hit.r.direction);
	ray = (t_ray){{5, 2, 0}, {-1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	is_hit_cylinder(cy, &ray, b, &hit);
	printf("Normal from +x:  expect (1, 0, 0)\n");
	debug_vec3("  actual", &hit.r.direction);
	ray = (t_ray){{5, 2, 5}, {-1, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	is_hit_cylinder(cy, &ray, b, &hit);
	printf("Normal from xz:  expect (0.707, 0, 0.707)\n");
	debug_vec3("  actual", &hit.r.direction);
}

// Tests height boundary conditions that affect the cylinder silhouette.
// m=0 and m=height are inclusive (valid hits on the edge of the tube).
// Rays above or below the finite height must miss the tube entirely.
static void	test_cy_height_bounds(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;
	bool		r;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 0, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Height m=0 (bottom edge): %s (expect HIT)\n", r ? "HIT" : "MISS");
	ray = (t_ray){{0, 4, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Height m=h (top edge):    %s (expect HIT)\n", r ? "HIT" : "MISS");
	ray = (t_ray){{0, 4.5, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Height m>h (above top):   %s (expect MISS)\n", r ? "HIT" : "MISS");
	ray = (t_ray){{0, -0.5, 5}, {0, 0, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Height m<0 (below bottom):%s (expect MISS)\n", r ? "HIT" : "MISS");
}

// Tests that the closest surface wins when tube and caps compete.
// Also tests a horizontal cylinder to verify axis-independent math.
static void	test_cy_surface_order(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;
	t_cylinder	cy_h;
	bool		r;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 5, 0.3}, {0, -1, -0.3}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Cap closer than tube:  %s (expect HIT)\n", r ? "HIT" : "MISS");
	if (r)
		printf("  y=%.1f (expect 4.0=top cap)\n", hit.r.origin.y);
	ray = (t_ray){{2, 2, 0}, {-1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Tube wins, no cap:     %s (expect HIT)\n", r ? "HIT" : "MISS");
	if (r)
		printf("  x=%.1f (expect 1.0=tube)\n", hit.r.origin.x);
	ft_bzero(&cy_h, sizeof(t_cylinder));
	cy_h.cylinder.r.origin = (t_vec3){0, 0, 5};
	cy_h.cylinder.r.direction = (t_vec3){1, 0, 0};
	cy_h.cylinder.length = 6.0;
	cy_h.radius = 1.0;
	ray = (t_ray){{0, 5, 5}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(&cy_h, &ray, b, &hit);
	printf("Horizontal cylinder:   %s (expect HIT)\n", r ? "HIT" : "MISS");
}

// Tests rays from inside the cylinder and self-intersection prevention.
// Inside hits must produce dot(ray_dir, normal) > 0 for inside_the_obj.
// Rays starting exactly on the surface must NOT self-intersect (SMALL_DOUBLE).
static void	test_cy_inside_and_self(t_cylinder *cy)
{
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	b;
	bool		r;

	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ray = (t_ray){{0, 2, 0}, {1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Inside to tube:     %s (expect HIT)\n", r ? "HIT" : "MISS");
	if (r)
		printf("  dot=%.1f (expect >0)\n",
			dot_vec3(ray.direction, hit.r.direction));
	ray = (t_ray){{0, 2, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Inside to top cap:  %s (expect HIT)\n", r ? "HIT" : "MISS");
	if (r)
		printf("  dot=%.1f (expect >0)\n",
			dot_vec3(ray.direction, hit.r.direction));
	ray = (t_ray){{1, 2, 0}, {1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Self-intersect tube:%s (expect MISS)\n", r ? "HIT" : "MISS");
	ray = (t_ray){{0, 4, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	r = is_hit_cylinder(cy, &ray, b, &hit);
	printf("Self-intersect cap: %s (expect MISS)\n", r ? "HIT" : "MISS");
}

// Runs all extended cylinder tests (normals, bounds, competition, inside).
// Uses same cylinder as basic tests: center=(0,2,0), axis=(0,1,0), r=1, h=4.
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
