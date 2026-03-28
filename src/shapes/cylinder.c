/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:11:05 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Initializes tube-intersection data in cylinder-local space. */
static bool	init_cy_tube(const t_cylinder *cy, const t_ray *ray,
		t_vec3 *bottom, t_cy_data *data)
{
	t_vec3	w;
	t_vec3	d_perp;
	t_vec3	w_perp;
	double	disc;

	*bottom = sub_vec3(cy->cylinder.r.origin,
			mul_one_vec3(cy->cylinder.r.direction, cy->cylinder.length * 0.5));
	w = sub_vec3(ray->origin, *bottom);
	data->dv = dot_vec3(ray->direction, cy->cylinder.r.direction);
	data->wv = dot_vec3(w, cy->cylinder.r.direction);
	d_perp = sub_vec3(ray->direction,
			mul_one_vec3(cy->cylinder.r.direction, data->dv));
	w_perp = sub_vec3(w, mul_one_vec3(cy->cylinder.r.direction, data->wv));
	data->a = dot_vec3(d_perp, d_perp);
	data->half_b = dot_vec3(d_perp, w_perp);
	data->c = dot_vec3(w_perp, w_perp) - cy->radius * cy->radius;
	disc = data->half_b * data->half_b - data->a * data->c;
	return (disc >= 0);
}

/* Tests ray vs. the infinite tube of the cylinder and fills the hit record. */
static bool	hit_cy_tube(const t_cylinder *cy, const t_ray *ray,
		t_interval b, t_norm_ray *hit)
{
	t_cy_data	data;
	t_vec3		bottom;
	double		disc;
	double		root;
	double		m;

	if (!init_cy_tube(cy, ray, &bottom, &data) || data.a < SMALL_DOUBLE)
		return (false);
	disc = sqrt(data.half_b * data.half_b - data.a * data.c);
	root = (-data.half_b - disc) / data.a;
	m = data.wv + root * data.dv;
	if (root <= b.min || root >= b.max || m < 0 || m > cy->cylinder.length)
	{
		root = (-data.half_b + disc) / data.a;
		m = data.wv + root * data.dv;
		if (root <= b.min || root >= b.max || m < 0 || m > cy->cylinder.length)
			return (false);
	}
	hit->length = root;
	hit->r.origin = get_pos_on_ray(ray, root);
	hit->r.direction = sub_vec3(sub_vec3(hit->r.origin, bottom),
			mul_one_vec3(cy->cylinder.r.direction, m));
	hit->r.direction = div_one_vec3(hit->r.direction, cy->radius);
	return (true);
}

/* Tests ray intersection against one cylinder end cap within the interval. */
static bool	hit_cy_single_cap(const t_ray *ray, t_interval *boarder,
		t_norm_ray *hit, const t_norm_ray *cap)
{
	t_vec3	dist_vec;
	double	denom;
	double	t;

	denom = dot_vec3(ray->direction, cap->r.direction);
	if (fabs(denom) < SMALL_DOUBLE)
		return (false);
	t = dot_vec3(sub_vec3(cap->r.origin, ray->origin),
			cap->r.direction) / denom;
	if (t <= boarder->min || t >= boarder->max)
		return (false);
	dist_vec = sub_vec3(get_pos_on_ray(ray, t), cap->r.origin);
	if (dot_vec3(dist_vec, dist_vec) > cap->length * cap->length)
		return (false);
	boarder->max = t;
	hit->length = t;
	hit->r.origin = get_pos_on_ray(ray, t);
	hit->r.direction = cap->r.direction;
	return (true);
}

/* Tests whether a ray hits a cylinder (tube or caps) within the interval. */
bool	is_hit_cylinder(const t_cylinder *cy, const t_ray *ray,
		const t_interval ray_boarder, t_norm_ray *hit)
{
	t_interval	b;
	t_norm_ray	cap;
	bool		found;

	b = ray_boarder;
	found = hit_cy_tube(cy, ray, b, hit);
	if (found)
		b.max = hit->length;
	cap.length = cy->radius;
	cap.r.direction = inverse_vec3(cy->cylinder.r.direction);
	cap.r.origin = sub_vec3(cy->cylinder.r.origin,
			mul_one_vec3(cy->cylinder.r.direction, cy->cylinder.length * 0.5));
	if (hit_cy_single_cap(ray, &b, hit, &cap))
		found = true;
	cap.r.direction = cy->cylinder.r.direction;
	cap.r.origin = add_vec3(cy->cylinder.r.origin,
			mul_one_vec3(cy->cylinder.r.direction, cy->cylinder.length * 0.5));
	if (hit_cy_single_cap(ray, &b, hit, &cap))
		found = true;
	return (found);
}

/* Finds the nearest cylinder hit across all cylinders in the scene. */
t_cylinder	*nearest_hit_cylinder(const t_ray *ray,
		t_interval *ray_boarder, t_norm_ray *hit)
{
	t_cylinder	*cy_hit;
	t_cylinder	*cy_loop;

	cy_hit = NULL;
	cy_loop = get_scene()->cylinders.first;
	while (cy_loop != get_scene()->cylinders.last)
	{
		if (is_hit_cylinder(cy_loop, ray, *ray_boarder, hit))
		{
			ray_boarder->max = hit->length;
			cy_hit = cy_loop;
		}
		cy_loop++;
	}
	return (cy_hit);
}
