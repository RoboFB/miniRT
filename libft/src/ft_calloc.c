/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:55:48 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc  R: *location or NULL  | Mallocs (nelem * elsize) and sets to zero
void	*ft_calloc(size_t nelem, size_t elsize)
{
	void	*location;

	location = malloc(nelem * elsize);
	if (location == NULL)
		return (NULL);
	ft_bzero(location, nelem * elsize);
	return (location);
}
