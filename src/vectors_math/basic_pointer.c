/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_pointer.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/12 12:18:17 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// *a + b
void	add_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x += b.x;
	a->y += b.y;
	a->z += b.z;
}

// *a - b
void	sub_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x -= b.x;
	a->y -= b.y;
	a->z -= b.z;
}

// *a * b
void	mul_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x *= b.x;
	a->y *= b.y;
	a->z *= b.z;
}

// *a / b
void	div_vec3_p(t_vec3 *a, const t_vec3 b)
{
	a->x /= b.x;
	a->y /= b.y;
	a->z /= b.z;
}

// *a + add
void	add_one_vec3_p(t_vec3 *a, const double add)
{
	a->x += add;
	a->y += add;
	a->z += add;
}

// *a - subtract
void	sub_one_vec3_p(t_vec3 *a, const double subtract)
{
	a->x -= subtract;
	a->y -= subtract;
	a->z -= subtract;
}

// *a * multiply
void	mul_one_vec3_p(t_vec3 *a, const double multiply)
{
	a->x *= multiply;
	a->y *= multiply;
	a->z *= multiply;
}

// *a / divide
void	div_one_vec3_p(t_vec3 *a, const double divide)
{
	a->x /= divide;
	a->y /= divide;
	a->z /= divide;
}
