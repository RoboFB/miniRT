/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array_access.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:47:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Returns a pointer to the element at the given index. */
void	*dynamic_array_get(t_dynamic_array *array, size_t idx)
{
	if (idx > array->elements_used)
		msg_exit("dynamic_array: idx out of bound");
	return (array->first + (idx * array->elements_size));
}

/* Returns a pointer to the last element in the array. */
void	*dynamic_array_get_last(t_dynamic_array *array)
{
	return (array->last);
}

/* Returns a pointer to the first element in the array. */
void	*dynamic_array_get_first(t_dynamic_array *array)
{
	return (array->first);
}
