/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/28 13:02:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/12 12:14:30 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"



// r: if true hit     only update hit if in range of boarder
bool	is_hit_sphere(const t_sphere *sph, const t_ray *ray, const t_interval ray_boarder, t_norm_ray *hit)
{
	t_vec3 oc = sub_vec3(sph->center, ray->origin);
	double a = length_squared_vec3(ray->direction);
	double h = dot_vec3(ray->direction, oc);
	double c = length_squared_vec3(oc) - sph->radius*sph->radius;
	double discriminant_squad = (h*h) - (a*c);
	// printf("discriminant: %f, a;%f, b;%f, c;%f\n", discriminant, a, b, c);	
	// debug_decimal("22 discriminant", discriminant);

	if (discriminant_squad < 0)
		return (false);

	double discriminant = sqrt(discriminant_squad);
	

	double root = (h - discriminant) / a;
	if (root <= ray_boarder.min || ray_boarder.max <= root)
	{
		root = (h + discriminant) / a;
		if (root <= ray_boarder.min || ray_boarder.max <= root)
			return false;
	}

	hit->length = root;// is length factor of a norm ray
	hit->r.origin = get_pos_on_ray(ray, hit->length);// hit point rec.p
	hit->r.direction = div_one_vec3(sub_vec3(hit->r.origin, sph->center), sph->radius);// rec.normal
	// printf("l:%.3f,", length_vec3(hit->r.direction));
	// printf("%.3f\n",hit->length);

	return (true);
}

// Returns the nearest sphere hit and updates ray_boarder and hit, or NULL.
t_sphere	*nearest_hit_sphere(const t_ray *ray, t_interval *ray_boarder,
			t_norm_ray *hit)
{
	t_sphere	*sphere_hit;
	t_sphere	*sphere_loop;

	sphere_hit = NULL;
	sphere_loop = get_scene()->spheres.first;
	while (sphere_loop != get_scene()->spheres.last)
	{
		if (is_hit_sphere(sphere_loop, ray, *ray_boarder, hit))
		{
			ray_boarder->max = hit->length;
			sphere_hit = sphere_loop;
		}
		sphere_loop++;
	}
	return (sphere_hit);
}

t_vec3 get_random_on_hemisphere(const t_vec3 *hit_direction_normal)
{
	t_vec3 new;
	
	new = get_random_unit_vector();
	if (dot_vec3(new, *hit_direction_normal) > 0.0) // In the same hemisphere as the normal
		return (new);
	else
		return (inverse_vec3(new));
}


