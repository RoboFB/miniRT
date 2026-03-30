/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_scalar.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:09:11 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vec3	add_one_vec3(t_vec3 a, const double add)
{
	a.x += add;
	a.y += add;
	a.z += add;
	return (a);
}

t_vec3	sub_one_vec3(t_vec3 a, const double subtract)
{
	a.x -= subtract;
	a.y -= subtract;
	a.z -= subtract;
	return (a);
}

t_vec3	mul_one_vec3(t_vec3 a, const double multiply)
{
	a.x *= multiply;
	a.y *= multiply;
	a.z *= multiply;
	return (a);
}

t_vec3	div_one_vec3(t_vec3 a, const double divide)
{
	a.x /= divide;
	a.y /= divide;
	a.z /= divide;
	return (a);
}
