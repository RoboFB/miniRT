/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:47:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/02/02 10:33:21 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"




// F: Mallocs | R: *pointer | E: first+last = NULL
t_dynamic_array	dynamic_array_init(size_t element_size)
{
	t_dynamic_array	array;

	array.elements_capacity = 8; // initial capacity
	array.elements_used = 0;
	array.elements_size = element_size; // set once at init


	array.first = ft_calloc(array.elements_capacity, array.elements_size);
	array.last = array.first;
	return (array);
}


void dynamic_array_add_back(t_dynamic_array *array, const void *item)
{
	if (array->elements_capacity == array->elements_used)
	{
		ft_realloc_2(&array->first, &array->last, &array->elements_capacity, array->elements_size);
	}
	array->elements_used++;
	ft_memcpy(array->last, item, array->elements_size);
	array->last+= array->elements_size;
	return ;
}


void *dynamic_array_get(t_dynamic_array *array, size_t idx)
{
	if (idx > array->elements_used)
		msg_exit("dynamic_array: idx out of bound");
	return (array->first + (idx*array->elements_size));
}

void dynamic_array_free(t_dynamic_array *array)
{
	free(array->first);
	array->first = NULL;
	array = NULL;
	return ;
}