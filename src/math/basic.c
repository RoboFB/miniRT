/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/09 18:00:54 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// a + b
t_vec3	add_vec3(t_vec3 a, const t_vec3 b)
{
	a.x += b.x;
	a.y += b.y;
	a.z += b.z;
	return (a);
}

// a - b
t_vec3	sub_vec3(t_vec3 a, const t_vec3 b)
{
	a.x -= b.x;
	a.y -= b.y;
	a.z -= b.z;
	return (a);
}

// a * b
t_vec3	mul_vec3(t_vec3 a, const t_vec3 b)
{
	a.x *= b.x;
	a.y *= b.y;
	a.z *= b.z;
	return (a);
}

// a / b
t_vec3	div_vec3(t_vec3 a, const t_vec3 b)
{
	a.x /= b.x;
	a.y /= b.y;
	a.z /= b.z;
	return (a);
}

// a + add
t_vec3	add_vec3_one(t_vec3 a, const double add)
{
	a.x += add;
	a.y += add;
	a.z += add;
	return (a);
}

// a - subtract
t_vec3	sub_vec3_one(t_vec3 a, const double subtract)
{
	a.x -= subtract;
	a.y -= subtract;
	a.z -= subtract;
	return (a);
}

// a * multiply
t_vec3	mul_vec3_one(t_vec3 a, const double multiply)
{
	a.x *= multiply;
	a.y *= multiply;
	a.z *= multiply;
	return (a);
}

// a / divide
t_vec3	div_vec3_one(t_vec3 a, const double divide)
{
	a.x /= divide;
	a.y /= divide;
	a.z /= divide;
	return (a);
}
