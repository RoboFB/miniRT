/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example_spheres_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 09:00:00 by ileon             #+#    #+#             */
/*   Updated: 2026/03/28 12:11:54 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	add_first_a(t_dynamic_array *spheres)
{
	t_sphere	s;

	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){0.0, -100.5, -1.0};
	s.radius = 100.0;
	s.material.type = MATERIAL_LAMBERTIAN;
	s.material.color = (t_vec3){0.8, 0.8, 0.0};
	dynamic_array_add_back_exit(spheres, &s);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){0.0, 0.0, -1.2};
	s.radius = 0.5;
	s.material.type = MATERIAL_LAMBERTIAN;
	s.material.color = (t_vec3){0.1, 0.2, 0.5};
	dynamic_array_add_back_exit(spheres, &s);
}

static void	add_first_b(t_dynamic_array *spheres)
{
	t_sphere	s;

	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){-1.0, 0.0, -1.0};
	s.radius = 0.5;
	s.material.type = MATERIAL_DIELECTRIC;
	s.material.refraction_index = 1.50;
	dynamic_array_add_back_exit(spheres, &s);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){-1.0, 0.0, -1.0};
	s.radius = 0.4;
	s.material.type = MATERIAL_DIELECTRIC;
	s.material.refraction_index = 1.0 / 1.50;
	dynamic_array_add_back_exit(spheres, &s);
	ft_bzero(&s, sizeof(t_sphere));
	s.center = (t_vec3){1.0, 0.0, -1.0};
	s.radius = 0.5;
	s.material.type = MATERIAL_REFLECTION;
	s.material.color = (t_vec3){0.8, 0.6, 0.2};
	s.material.fuzz = 1;
	dynamic_array_add_back_exit(spheres, &s);
}

void	example_first_spheres(t_dynamic_array *spheres)
{
	add_first_a(spheres);
	add_first_b(spheres);
}
