/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_plane.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 09:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/28 12:10:07 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	print_result(const char *label, bool result, bool expect)
{
	if (result == expect)
		printf("%s: OK\n", label);
	else
		printf("%s: FAIL\n", label);
}

static void	test_plane_group_a(t_plane *pl, t_interval b)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		result;

	ray = (t_ray){{0, 0, 0}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 1 - ray down (expect true)", result, true);
	ray = (t_ray){{0, 0, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 2 - ray up (expect false)", result, false);
	ray = (t_ray){{0, 0, 0}, {1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 3 - ray parallel (expect false)", result, false);
}

static void	test_plane_group_b(t_plane *pl, t_interval b)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		result;

	ray = (t_ray){{0, 0, 0}, {1, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 4 - ray diagonal (expect true)", result, true);
	ray = (t_ray){{0, -5, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 5 - ray from below (expect true)", result, true);
	ray = (t_ray){{0, 0, 0}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, (t_interval){SMALL_DOUBLE, 1.0}, &hit);
	print_result("Test 6 - boarder max=1 (expect false)", result, false);
	ray = (t_ray){{0, -2, 0}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 7 - on plane (expect false)", result, false);
}

static void	test_plane_group_c(t_plane *pl, t_interval b)
{
	t_ray		ray;
	t_norm_ray	hit;
	bool		result;

	pl->plane.origin = (t_vec3){0, 0, 10};
	pl->plane.direction = (t_vec3){0, 0, -1};
	ray = (t_ray){{0, 0, 0}, {0, 0, 1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 8 - wall plane (expect true)", result, true);
	pl->plane.origin = (t_vec3){0, 0, 0};
	pl->plane.direction = normalize_vec3((t_vec3){0, 1, 1});
	ray = (t_ray){{0, 5, 5}, {0, -1, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 9 - tilted 45deg (expect true)", result, true);
	pl->plane.origin = (t_vec3){0, -2, 0};
	pl->plane.direction = (t_vec3){0, 1, 0};
	ray = (t_ray){{0, 0, 0}, {1, -0.001, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(pl, &ray, b, &hit);
	print_result("Test 10 - grazing ray (expect true)", result, true);
}

void	test_hit_plane(void)
{
	t_plane		pl;
	t_interval	b;

	pl.plane.origin = (t_vec3){0, -2, 0};
	pl.plane.direction = (t_vec3){0, 1, 0};
	b = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	test_plane_group_a(&pl, b);
	test_plane_group_b(&pl, b);
	test_plane_group_c(&pl, b);
}
