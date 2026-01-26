/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:16:57 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: ok: len(src+dst) or nok: dstsize + len(src)
// E: copy (src) to end of (dst). until dstsize full, null terminates dst
size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	len_dst;
	size_t	idx_src;

	len_dst = ft_strlen(dst);
	idx_src = 0;
	if (dstsize <= len_dst)
		return (dstsize + ft_strlen(src));
	while (src[idx_src] && dstsize > (idx_src + len_dst + 1))
	{
		dst[len_dst + idx_src] = src[idx_src];
		idx_src++;
	}
	dst[len_dst + idx_src] = '\0';
	return (len_dst + ft_strlen(src));
}
