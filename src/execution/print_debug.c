/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:06:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/17 15:51:35 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	debug_vec3(const char *msg, const t_vec3 *v)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (x%f, y%f, z%f)\n", msg, v->x, v->y, v->z);
}

void	debug_ray(const char *msg, const t_ray *ray)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: origin: (%.3f, %.3f, %.3f)   direction: (%.3f ,%.3f ,%.3f)\n", 
		msg, 
		ray->origin.x, ray->origin.y, ray->origin.z, 
		ray->direction.x, ray->direction.y, ray->direction.z);
}

void	debug_decimal(const char *msg, double d)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (%.3f)\n", msg, d);
}

void debug_material(const t_material *material)
{
	if (DEBUG_RT == 0)
		return ;
	if (material->type == MATERIAL_NONE)
		printf("Material: NONE\n");
	else if (material->type == MATERIAL_LAMBERTIAN)
		printf("Material: LAMBERTIAN\n");
	else if (material->type == MATERIAL_METAL)
		printf("Material: METAL\n");
	else if (material->type == MATERIAL_DIELECTRIC)
		printf("Material: DIELECTRIC\n");
	else if (material->type == MATERIAL_ALL)
		printf("Material: ALL\n");
	else
		printf("Material: UNKNOWN\n");
	debug_vec3("color", &material->color);
	debug_decimal("fuzz", material->fuzz);
	debug_decimal("refraction_index", material->refraction_index);
}

void debug_sphere(const t_sphere *sph)
{
	if (DEBUG_RT == 0)
		return ;
	printf("Sphere:\n");
	debug_vec3("center", &sph->center);
	debug_decimal("radius", sph->radius);
	debug_material(&sph->material);
}
