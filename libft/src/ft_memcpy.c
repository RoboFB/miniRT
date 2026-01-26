/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 12:54:53 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: void *dst | E: copy memory(src) to (dst) len(n) times. needs no overlap!
void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*dst_base;
	unsigned char	*src_base;
	size_t			idx;

	if (dst == src)
		return (dst);
	dst_base = (unsigned char *)dst;
	src_base = (unsigned char *)src;
	idx = (size_t)0;
	while (idx < n)
	{
		dst_base[idx] = src_base[idx];
		idx++;
	}
	return (dst);
}
