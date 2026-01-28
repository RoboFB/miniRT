/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/28 18:22:29 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

double	hit_sphere(t_vec3 start, double radius, const t_ray *ray)
{
	start  = vec3_sub(start, ray->origin);
	double a = vec3_dot(ray->direction, ray->direction);
	double b = -2.0 * vec3_dot(ray->direction, start);
	double c = vec3_dot(start, start) - radius*radius;
	double discriminant = (b*b) - (4.0*a*c);
	// printf("discriminant: %f, a;%f, b;%f, c;%f\n", discriminant, a, b, c);
	
	// debug_decimal("22 discriminant", discriminant);

	if (discriminant < 0)
	{
		// printf("                 YES\n");
		return (-1.0);
	}
	else
	{
		// printf("                 NO\n");
		return ((-b - sqrt(discriminant) ) / (2.0*a));
	}
	
}

