/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 12:56:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: void *dst | E: move memory(src) to (dst) len(n) times. !can overlap!
void	*ft_memmove(void *dst, const void *src, size_t len)
{
	size_t			idx;

	if (dst == src)
		return (dst);
	idx = 0;
	if (dst < src)
	{
		while (idx < len)
		{
			((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
			idx++;
		}
	}
	else
	{
		idx = len;
		while (idx)
		{
			idx--;
			((unsigned char *)dst)[idx] = ((unsigned char *)src)[idx];
		}
	}
	return (dst);
}
