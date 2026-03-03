/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   allocs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/30 17:30:08 by rgohrig           #+#    #+#             */
/*   Updated: 2026/03/03 18:07:45 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "mini_rt.h"

// R: (Ok)*new pointer  (Error) NULL + printed perror msg
void *calloc_perror(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
	{
		perror("Malloc error in calloc_perror");
		return (NULL);
	}
	else
	{
		return (ptr);
	}
}

// R: (Ok)*new pointer  (Error) exit
void *calloc_perror_exit(size_t count, size_t size)
{
	void	*ptr;

	ptr = ft_calloc(count, size);
	if (ptr == NULL)
	{
		perror_exit("Malloc error in calloc_perror_exit");
		return (NULL);
	}
	else
	{
		return (ptr);
	}
}

// R: (OK)*new_ptr (Error) NULL + printed perror msg
// sets to zero and copy ptr to new-ptr cuts if new is smaller
void	ft_realloc_perror(void **change_ptr, size_t old, size_t new, size_t size)
{
	void	*new_ptr;

	if (change_ptr == NULL || old == 0 || new == 0 || size == 0 || old == new)
		return ;
	new_ptr = calloc_perror(new, size);
	if (new_ptr == NULL)
	{
		free(*change_ptr);
		*change_ptr = NULL;
		return ;
	}
	if (new > old)
		ft_memcpy(new_ptr, *change_ptr, old * size);
	else
		ft_memcpy(new_ptr, *change_ptr, new * size);
	free(*change_ptr);
	*change_ptr = new_ptr;
	return ;
}

int	ft_realloc_perror_2(void **change_first, void **change_last, size_t *elements_count, size_t size)
{
	size_t	new_count;

	new_count = *elements_count * 2;
	ft_realloc_perror(change_first, *elements_count, new_count, size);
	if (*change_first == NULL)
	{
		*change_last = NULL;
		*elements_count = 0;
		return (-1);
	}
	*change_last = *change_first + ((*elements_count) * size);
	*elements_count = new_count;
	return (0);
}
