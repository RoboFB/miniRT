/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 18:52:13 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/06 17:47:58 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"


// ray: the one ray that i test if it hit somting its the in start ray
// hit: the normalized ray on the hit form the hit (to/from not sure) center

// aka ray_color
t_vec3	ray_to_color(const t_ray *ray, int depth)
{

	t_sphere	*sphere_hit;
	t_norm_ray	hit;
	t_interval ray_boarder;
	
	
	if (depth-- == 0)
		return (BLACK_VEC3);
	
	ray_boarder.min = SMALL_DOUBLE;
	ray_boarder.max = BIG_DOUBLE;
	ft_bzero(&hit, sizeof(t_norm_ray));
	sphere_hit = nearest_hit_sphere(ray, &ray_boarder, &hit);

	// added here hit_plane, hit_cylinder

	if (sphere_hit == NULL)
		return (background_color(ray));
	else if (dot_vec3(ray->direction, hit.r.direction) > 0.0)
		return (inside_the_obj(&sphere_hit->material, &hit, ray, depth));
	else
		return (outside_the_obj(&sphere_hit->material, &hit, ray, depth));
}

// R: the nearest sphere and updates ray_bound and hit for it or NULL at no hit
t_sphere *nearest_hit_sphere(const t_ray *ray, t_interval *ray_boarder, t_norm_ray *hit)
{
	t_sphere	*sphere_hit;
	t_sphere	*sphere_loop;

	sphere_hit = NULL;
	sphere_loop = get_scene()->spheres.first;
	while (sphere_loop != get_scene()->spheres.last)
	{
		if (is_hit_sphere(sphere_loop, ray, *ray_boarder, hit)) // hit
		{
			ray_boarder->max = hit->length; // update ray boarder to closest hit
			sphere_hit = sphere_loop;
		}
		sphere_loop++;
	}
	return (sphere_hit);
}

t_vec3 background_color(const t_ray *ray)
{
	t_vec3 color;

	t_vec3 norm_direction = normalize_vec3(ray->direction);
	double a = 0.5*(norm_direction.y + 1.0);
	
	color.x = (1.0 - a) *1.0 + (a * 0.5);
	color.y = (1.0 - a) *1.0 + (a * 0.7);
	color.z = (1.0 - a) *1.0 + (a * 1.0);
	return (color);
	// return get_scene()->ambient_light->color; //altnative options
	// return BLACK_VEC3; //altnative options
}


t_vec3 outside_the_obj(const t_material *material, const t_norm_ray *hit, const t_ray *ray, int depth)
{
	t_ray scattered = {0};

	if (material->type & MATERIAL_PHONG)
	{
		return (phone_color(material, hit, ray));
	}
	if (material->type & MATERIAL_LAMBERTIAN)
	{
		if (scatter_lambertian(hit, &scattered))
			return (mul_vec3(ray_to_color(&scattered, depth), material->color));
	}
	else if (material->type & MATERIAL_REFLECTION)
	{
		if (scatter_metal(ray, hit, &scattered, material))
			return (mul_vec3(ray_to_color(&scattered, depth), material->color));
	}
	else if (material->type & MATERIAL_DIELECTRIC)
	{
		double ri = (1.0/material->refraction_index);
		if (scatter_dielectric(ray, hit, &scattered, ri))
			return (mul_vec3(ray_to_color(&scattered, depth), WHITE_VEC3));
	}
	return (BLACK_VEC3);
}

// not so importance mostly for dielectric materials(galas)
t_vec3 inside_the_obj(const t_material *material, t_norm_ray *hit, const t_ray *ray, int depth)
{
	t_ray scattered = {0};

	hit->r.direction = inverse_vec3(hit->r.direction);

	if (material->type & MATERIAL_DIELECTRIC)
	{
		double ri = material->refraction_index;
		if (scatter_dielectric(ray, hit, &scattered, ri))
			return (mul_vec3(ray_to_color(&scattered, depth), WHITE_VEC3));
	}
	return (BLACK_VEC3);
}

t_vec3 phone_color(const t_material *material, const t_norm_ray *hit, const t_ray *ray)
{
	(void)hit;
	(void)ray;

	t_vec3	color;
	t_scene * const scene = &get_data()->scene;
	t_dynamic_array lights = scene->lights;

	// ambient light
	color = mul_one_vec3(scene->ambient_light->color, scene->ambient_light->ratio);

	
	t_light	*light = lights.first;
	while (light != lights.last)
	{
		t_ray light_ray;
		light_ray.origin = hit->r.origin;
		light_ray.direction = light->position;

		t_interval light_ray_boarder = {SMALL_DOUBLE, BIG_DOUBLE};// maybe remove big and use the length between light pos and hit pos
		
		if (nearest_hit_sphere(&light_ray, &light_ray_boarder, &(t_norm_ray){0}) == NULL)
		{
			// 
			t_vec3 light_color = mul_one_vec3(light->color, light->ratio);
			add_vec3_p(&color, light_color);

			// diffuse light
			double lightIntensity = fmax(dot_vec3(NormVec, SunDirectionObjSpc), 0.0);
			t_vec3 diffuse = 0.9 * lightIntensity * lightColor * textureColor;

			
		}
		
		light++;
	}
	

	clamp_vec3_p(&color, (t_interval){0.0, 1.0});
	
	
	mul_vec3_p(&color, material->color); // add matiral color at the end
	return color;
}