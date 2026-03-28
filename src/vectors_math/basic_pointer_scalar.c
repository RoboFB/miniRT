/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic_pointer_scalar.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ileon <ileon@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/02 11:03:36 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 12:09:28 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	add_one_vec3_p(t_vec3 *a, const double add)
{
	a->x += add;
	a->y += add;
	a->z += add;
}

void	sub_one_vec3_p(t_vec3 *a, const double subtract)
{
	a->x -= subtract;
	a->y -= subtract;
	a->z -= subtract;
}

void	mul_one_vec3_p(t_vec3 *a, const double multiply)
{
	a->x *= multiply;
	a->y *= multiply;
	a->z *= multiply;
}

void	div_one_vec3_p(t_vec3 *a, const double divide)
{
	a->x /= divide;
	a->y /= divide;
	a->z /= divide;
}
