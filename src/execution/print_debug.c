/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 16:06:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Prints a labeled vec3 value to stdout. */
void	debug_vec3(const char *msg, const t_vec3 *v)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (x%.3f, y%.3f, z%.3f)\n", msg, v->x, v->y, v->z);
}

/* Prints a labeled ray (origin + direction) to stdout. */
void	debug_ray(const char *msg, const t_ray *ray)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: origin:(%.3f,%.3f,%.3f) dir:(%.3f,%.3f,%.3f)\n",
		msg, ray->origin.x, ray->origin.y, ray->origin.z,
		ray->direction.x, ray->direction.y, ray->direction.z);
}

/* Prints a labeled double value to stdout. */
void	debug_decimal(const char *msg, double d)
{
	if (DEBUG_RT == 0)
		return ;
	printf("%s: (%.3f)\n", msg, d);
}

/* Prints material type and all properties to stdout. */
void	debug_material(const t_material *material)
{
	if (DEBUG_RT == 0)
		return ;
	if (material->type == MATERIAL_NONE)
		printf("Material: NONE\n");
	else if (material->type == MATERIAL_LAMBERTIAN)
		printf("Material: LAMBERTIAN\n");
	else if (material->type == MATERIAL_REFLECTION)
		printf("Material: METAL\n");
	else if (material->type == MATERIAL_DIELECTRIC)
		printf("Material: DIELECTRIC\n");
	else
		printf("Material: UNKNOWN\n");
	debug_vec3("color", &material->color);
	debug_decimal("fuzz", material->fuzz);
	debug_decimal("refraction_index", material->refraction_index);
}

/* Prints sphere center and radius to stdout. */
void	debug_sphere(const t_sphere *sph)
{
	if (DEBUG_RT == 0)
		return ;
	printf("Sphere:\n");
	debug_vec3("center", &sph->center);
	debug_decimal("radius", sph->radius);
	debug_material(&sph->material);
}
