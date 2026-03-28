/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynamic_array.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/30 12:47:59 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/28 09:00:00 by ileon            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* Creates an empty dynamic array with the given element size; exits on err. */
t_dynamic_array	dynamic_array_init_exit(size_t element_size)
{
	t_dynamic_array	array;

	array.elements_capacity = 8;
	array.elements_used = 0;
	array.elements_size = element_size;
	array.first = calloc_perror_exit(array.elements_capacity,
			array.elements_size);
	array.last = array.first;
	return (array);
}

/* Appends an element to the back of the array; exits on allocation failure. */
void	dynamic_array_add_back_exit(t_dynamic_array *array, const void *item)
{
	if (array->elements_capacity == array->elements_used)
	{
		if (ft_realloc_perror_2(&array->first, &array->last,
				&array->elements_capacity, array->elements_size) == -1)
			program_exit(EXIT_FAILURE);
	}
	array->elements_used++;
	ft_memcpy(array->last, item, array->elements_size);
	array->last += array->elements_size;
}

/* Appends an element to the back of the array; returns -1 on failure. */
int	dynamic_array_add_back_perror(t_dynamic_array *array, const void *item)
{
	if (array->elements_capacity == array->elements_used)
	{
		if (ft_realloc_perror_2(&array->first, &array->last,
				&array->elements_capacity, array->elements_size) == -1)
			return (-1);
	}
	array->elements_used++;
	ft_memcpy(array->last, item, array->elements_size);
	array->last += array->elements_size;
	return (0);
}

/* Frees the array's backing buffer and resets all fields to zero. */
void	dynamic_array_free(t_dynamic_array *array)
{
	if (array == NULL)
		return ;
	if (array->first != NULL)
		free(array->first);
	array->first = NULL;
	array->last = NULL;
	array->elements_used = 0;
	array->elements_size = 0;
	array->elements_capacity = 0;
}
