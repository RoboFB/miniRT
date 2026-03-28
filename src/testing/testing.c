/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   testing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 18:51:47 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/19 13:45:07 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// dirty testing for random number generator
void test_r3(void)
{
	for (int i = 0; i < 10000000; i++)
	{
		t_vec3 v3 = get_random_unit_vector();
		// debug_vec3("r3", &v3);
		printf("_lengt:_%f\n", length_vec3(v3));
		(void)v3;
	}
}

// dirty testing for random number generator
void test_random(void)
{
	double	result;

	int testing[10] = {0};

	for (int i = 0; i < 1000000; i++)
	{
		result = get_random();
		printf("random: %f\n", result);
		if (result >= 0.0 && result < 0.1)
			testing[0]++;
		else if (result >= 0.1 && result < 0.2)
			testing[1]++;
		else if (result >= 0.2 && result < 0.3)
			testing[2]++;
		else if (result >= 0.3 && result < 0.4)
			testing[3]++;
		else if (result >= 0.4 && result < 0.5)
			testing[4]++;
		else if (result >= 0.5 && result < 0.6)
			testing[5]++;
		else if (result >= 0.6 && result < 0.7)
			testing[6]++;
		else if (result >= 0.7 && result < 0.8)
			testing[7]++;
		else if (result >= 0.8 && result < 0.9)
			testing[8]++;
		else if (result >= 0.9 && result < 1.0)
			testing[9]++;
		else
		{
			printf("Error: random number out of bounds: %f\n", result);
			exit(1);
		}
	}
	printf("Results after 1,000,000 iterations:\n");
	for (int i = 0; i < 10; i++)
	{
		printf("Range %i: %d\n", i, testing[i]);
	}
}

void test_dynamic_array(void)
{
	t_dynamic_array ar;

	ar = dynamic_array_init_exit(sizeof(double));

	double *head = ar.first;


	dynamic_array_add_back_exit(&ar, &(double){0});
	dynamic_array_add_back_exit(&ar, &(double){1});
	dynamic_array_add_back_exit(&ar, &(double){2});
	dynamic_array_add_back_exit(&ar, &(double){3});
	dynamic_array_add_back_exit(&ar, &(double){4});
	dynamic_array_add_back_exit(&ar, &(double){5});
	dynamic_array_add_back_exit(&ar, &(double){6});
	dynamic_array_add_back_exit(&ar, &(double){7});
	dynamic_array_add_back_exit(&ar, &(double){8});
	dynamic_array_add_back_exit(&ar, &(double){9});
	dynamic_array_add_back_exit(&ar, &(double){10});
	dynamic_array_add_back_exit(&ar, &(double){11});

	head = ar.first;
	while (head != ar.last)
	{
		/* code */
		printf("value: %.2f\n", *head);
		head++;
	}
	
	printf("\n");
	uint32_t idx = 0;
	while (idx < ar.elements_used)
	{
		double *current = dynamic_array_get(&ar, idx);
		/* code */


		printf("value: %.2f\n", *current);
		idx++;
	}


	dynamic_array_free(&ar);
}


// testet is_hit_plane mit 10 Faellen
// Setup: Bodenebene bei y=-2, Normale zeigt nach oben (0,1,0)
//   pl 0,-2,0  0,1,0  0,255,0
//
//         Kamera (0,0,0)
//            |
//            | Ray nach unten (0,-1,0)
//            v
//   =========*========= Ebene bei y = -2
//        Hit bei (0,-2,0)
//
void	test_hit_plane(void)
{
	t_plane		pl;
	t_ray		ray;
	t_norm_ray	hit;
	t_interval	boarder;
	bool		result;

	// Setup: Bodenebene bei y=-2, Normale zeigt nach oben
	pl.plane.origin = (t_vec3){0, -2, 0};
	pl.plane.direction = (t_vec3){0, 1, 0};
	boarder = (t_interval){SMALL_DOUBLE, BIG_DOUBLE};
	ft_bzero(&hit, sizeof(t_norm_ray));

	// Test 1: Ray gerade nach unten -> trifft bei t=2
	// Ray startet am Ursprung, geht nach unten. Ebene ist 2 Einheiten darunter.
	// t = dot((0,-2,0)-(0,0,0), (0,1,0)) / dot((0,-1,0), (0,1,0))
	// t = dot((0,-2,0), (0,1,0)) / dot((0,-1,0), (0,1,0))
	// t = -2 / -1 = 2
	ray = (t_ray){{0, 0, 0}, {0, -1, 0}};
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 1 - ray down:      %s (expect true)\n", result ? "HIT" : "MISS");
	if (result)
	{
		debug_decimal("  t", hit.length);
		debug_vec3("  hit point", &hit.r.origin);
		debug_vec3("  normal", &hit.r.direction);
	}

	// Test 2: Ray nach oben -> kein Hit (Ebene ist unten, Ray geht weg)
	// t = -2 / 1 = -2 (negativ = hinter der Kamera = kein Hit)
	ray = (t_ray){{0, 0, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 2 - ray up:        %s (expect false)\n", result ? "HIT" : "MISS");

	// Test 3: Ray parallel zur Ebene -> kein Hit (denom ~ 0)
	// dot((1,0,0), (0,1,0)) = 0 -> parallel
	ray = (t_ray){{0, 0, 0}, {1, 0, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 3 - ray parallel:  %s (expect false)\n", result ? "HIT" : "MISS");

	// Test 4: Ray diagonal -> trifft
	// Ray geht (1,-1,0), Ebene bei y=-2
	// t = dot((0,-2,0), (0,1,0)) / dot((1,-1,0), (0,1,0))
	// t = -2 / -1 = 2, Hit bei (0,0,0) + 2*(1,-1,0) = (2,-2,0)
	ray = (t_ray){{0, 0, 0}, {1, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 4 - ray diagonal:  %s (expect true)\n", result ? "HIT" : "MISS");
	if (result)
	{
		debug_decimal("  t", hit.length);
		debug_vec3("  hit point", &hit.r.origin);
		debug_vec3("  normal", &hit.r.direction);
	}

	// Test 5: Ray von unterhalb der Ebene nach oben -> trifft
	// Kamera bei (0,-5,0), Ray nach oben (0,1,0), Ebene bei y=-2
	// t = dot((0,-2,0)-(0,-5,0), (0,1,0)) / dot((0,1,0), (0,1,0))
	// t = dot((0,3,0), (0,1,0)) / 1 = 3
	ray = (t_ray){{0, -5, 0}, {0, 1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 5 - ray from below: %s (expect true)\n", result ? "HIT" : "MISS");
	if (result)
	{
		debug_decimal("  t", hit.length);
		debug_vec3("  hit point", &hit.r.origin);
	}

	// Test 6: ray_boarder begrenzt den Hit -> t=2 aber boarder.max=1 -> kein Hit
	// gleicher Ray wie Test 1, aber max Distanz auf 1 begrenzt
	ray = (t_ray){{0, 0, 0}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, (t_interval){SMALL_DOUBLE, 1.0}, &hit);
	printf("Test 6 - boarder max=1: %s (expect false)\n", result ? "HIT" : "MISS");

	// Test 7: Ray startet genau auf der Ebene -> t~0, unter SMALL_DOUBLE -> kein Hit
	// verhindert Self-Intersection (gleicher Grund warum Spheres SMALL_DOUBLE nutzen)
	ray = (t_ray){{0, -2, 0}, {0, -1, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 7 - on plane:      %s (expect false)\n", result ? "HIT" : "MISS");

	// Test 8: vertikale Wand-Ebene (Normale zeigt in z-Richtung)
	// Wand bei z=10, Normale (0,0,-1) zeigt zur Kamera
	pl.plane.origin = (t_vec3){0, 0, 10};
	pl.plane.direction = (t_vec3){0, 0, -1};
	ray = (t_ray){{0, 0, 0}, {0, 0, 1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 8 - wall plane:    %s (expect true)\n", result ? "HIT" : "MISS");
	if (result)
	{
		debug_decimal("  t", hit.length);
		debug_vec3("  hit point", &hit.r.origin);
		debug_vec3("  normal", &hit.r.direction);
	}

	// Test 9: gekippte Ebene bei 45 Grad, Normale (0, 0.707, 0.707)
	// Ebene am Ursprung, Ray von (0,5,5) Richtung (0, -1, -1)
	// trifft am Ursprung der Ebene
	pl.plane.origin = (t_vec3){0, 0, 0};
	pl.plane.direction = normalize_vec3((t_vec3){0, 1, 1});
	ray = (t_ray){{0, 5, 5}, {0, -1, -1}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 9 - tilted 45deg:  %s (expect true)\n", result ? "HIT" : "MISS");
	if (result)
	{
		debug_decimal("  t", hit.length);
		debug_vec3("  hit point", &hit.r.origin);
	}

	
	// Test 10: Ray fast parallel (streifender Winkel) -> trifft trotzdem
	// Bodenebene bei y=-2, Ray-Richtung (1, -0.001, 0) -> sehr flach
	// t = -2 / -0.001 = 2000, Hit weit weg bei (2000, -2, 0).
	pl.plane.origin = (t_vec3){0, -2, 0};
	pl.plane.direction = (t_vec3){0, 1, 0};
	ray = (t_ray){{0, 0, 0}, {1, -0.001, 0}};
	ft_bzero(&hit, sizeof(t_norm_ray));
	result = is_hit_plane(&pl, &ray, boarder, &hit);
	printf("Test 10 - grazing ray:  %s (expect true)\n", result ? "HIT" : "MISS");
	if (result)
	{
		debug_decimal("  t", hit.length);
		debug_vec3("  hit point", &hit.r.origin);
	}
}

int test_caller(int argc, char const *argv[])
{
	if (DEBUG_RT == 0)
		return (0);
	if (argc != 3)
		return (0);
	if (ft_strncmp(argv[1], "-t", 3) != 0
		&& ft_strncmp(argv[1], "--test", 7) != 0)
		return (0);
	if (ft_strncmp(argv[2], "dynamic_array", 15) == 0)
	{
		test_dynamic_array();
		return (1);
	}
	if (ft_strncmp(argv[2], "random", 7) == 0)
	{
		test_random();
		return (1);
	}
	if (ft_strncmp(argv[2], "r3", 3) == 0)
	{
		test_r3();
		return (1);
	}
	if (ft_strncmp(argv[2], "hit_plane", 10) == 0)
	{
		test_hit_plane();
		return (1);
	}
	if (ft_strncmp(argv[2], "hit_cylinder", 13) == 0)
	{
		test_hit_cylinder();
		test_hit_cylinder_ext();
		return (1);
	}
	return (0);
}