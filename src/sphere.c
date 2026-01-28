/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/28 19:11:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

double	hit_sphere(t_vec3 center, double radius, const t_ray *ray)
{
	center = vec3_sub(center, ray->origin);
	double a = vec3_combine(vec3_square(ray->direction));
	double h = vec3_dot(ray->direction, center);
	double c = vec3_combine(vec3_square(center)) - radius*radius;
	double discriminant = (h*h) - (a*c);
	// printf("discriminant: %f, a;%f, b;%f, c;%f\n", discriminant, a, b, c);	
	// debug_decimal("22 discriminant", discriminant);

	if (discriminant < 0)
		return (-1.0);
	return ((h - sqrt(discriminant) ) / a);
}

