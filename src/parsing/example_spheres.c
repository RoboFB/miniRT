/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_spheres.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/03 17:58:29 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:11:47 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	add_purple_a(t_dynamic_array *spheres)
{
	t_sphere	s;

	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){-0.5, 0.0, -1.0};
	s.radius = 0.5;
	s.material.type = MATERIAL_LAMBERTIAN;
	s.material.color = (t_vec3){0.1, 0.000001, 0.1};
	dynamic_array_add_back_exit(spheres, &s);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){0.0, -100.5, -1.0};
	s.radius = 100.0;
	s.material.type = MATERIAL_REFLECTION;
	s.material.color = (t_vec3){0.7, 0.7, 0.7};
	s.material.fuzz = 0.01;
	dynamic_array_add_back_exit(spheres, &s);
}

static void	add_purple_b(t_dynamic_array *spheres)
{
	t_sphere	s;

	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){0.5, 0.2, -1.0};
	s.radius = 0.4;
	s.material.type = MATERIAL_DIELECTRIC;
	s.material.color = (t_vec3){0.7, 0.7, 0.7};
	s.material.refraction_index = 1.0 / 1.5;
	dynamic_array_add_back_exit(spheres, &s);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){0.5, 0.2, -1.0};
	s.radius = 0.5;
	s.material.type = MATERIAL_DIELECTRIC;
	s.material.color = (t_vec3){0.7, 0.7, 0.7};
	s.material.refraction_index = 1.0;
	dynamic_array_add_back_exit(spheres, &s);
}

void	example_purple_spheres(t_dynamic_array *spheres)
{
	add_purple_a(spheres);
	add_purple_b(spheres);
}

void	example_fov_spheres(t_dynamic_array *spheres)
{
	t_sphere	s;
	double		radius;

	radius = cos(M_PI / 4.0);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){-radius, 0.0, -1.0};
	s.radius = radius;
	s.material.type = MATERIAL_LAMBERTIAN;
	s.material.color = (t_vec3){0.0, 0.0, 1.0};
	dynamic_array_add_back_exit(spheres, &s);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){radius, 0.0, -1.0};
	s.radius = radius;
	s.material.type = MATERIAL_LAMBERTIAN;
	s.material.color = (t_vec3){1.0, 0.0, 0.0};
	dynamic_array_add_back_exit(spheres, &s);
}
