/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:47:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/03 19:33:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"


// F: Mallocs | R: *pointer | E: first+last = NULL
t_dynamic_array	dynamic_array_init_exit(size_t element_size)
{
	t_dynamic_array	array;

	array.elements_capacity = 8; // initial capacity
	array.elements_used = 0;
	array.elements_size = element_size; // set once at init


	array.first = calloc_perror_exit(array.elements_capacity, array.elements_size);
	array.last = array.first;
	return (array);
}

void dynamic_array_add_back_exit(t_dynamic_array *array, const void *item)
{
	if (array->elements_capacity == array->elements_used)
	{
		if (ft_realloc_perror_2(&array->first, &array->last, &array->elements_capacity, array->elements_size) == -1)
			program_exit(EXIT_FAILURE);
	}
	array->elements_used++;
	ft_memcpy(array->last, item, array->elements_size);
	array->last+= array->elements_size;
	return ;
}

// R: (Error) -1   (OK)0
int dynamic_array_add_back_perror(t_dynamic_array *array, const void *item)
{
	if (array->elements_capacity == array->elements_used)
	{
		if (ft_realloc_perror_2(&array->first, &array->last, &array->elements_capacity, array->elements_size) == -1)
			return (-1);
	}
	array->elements_used++;
	ft_memcpy(array->last, item, array->elements_size);
	array->last+= array->elements_size;
	return (0);
}

void *dynamic_array_get(t_dynamic_array *array, size_t idx)
{
	if (idx > array->elements_used)
		msg_exit("dynamic_array: idx out of bound");
	return (array->first + (idx*array->elements_size));
}

void *dynamic_array_get_last(t_dynamic_array *array)
{
	return (array->last);
}

void *dynamic_array_get_first(t_dynamic_array *array)
{
	return (array->first);
}

// frees and resets array and sets this pointer to Null
void dynamic_array_free(t_dynamic_array *array)
{
	if (array == NULL)
		return;
	if (array->first != NULL)
		free(array->first);
	array->first = NULL;
	array->last = NULL;
	array->elements_used = 0;
	array->elements_size = 0;
	array->elements_capacity = 0;
	array = NULL;
	return;
}
