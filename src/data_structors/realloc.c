/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:30:08 by rgohrig           #+#    #+#             */
/*   Updated: 2026/01/30 19:53:04 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// R: *new_ptr
// sets to zero and copy ptr to new-ptr cuts if new is smaller
void	ft_realloc(void **change_ptr, size_t old, size_t new, size_t size)
{
	void	*new_ptr;

	if (change_ptr == NULL || old == 0 || new == 0 || size == 0 || old == new)
		return ;
	new_ptr = ft_calloc(new, size);
	if (new > old)
		ft_memcpy(new_ptr, *change_ptr, old * size);
	else
		ft_memcpy(new_ptr, *change_ptr, new * size);
	free(*change_ptr);
	*change_ptr = new_ptr;
	return ;
}

void	ft_realloc_2(void **change_first, void **change_last, size_t *elements_count, size_t size)
{
	size_t	new_count;

	new_count = *elements_count * 2;
	ft_realloc(change_first, *elements_count, new_count, size);
	*change_last = *change_first + ((*elements_count) * size);
	*elements_count = new_count;
	return ;
}