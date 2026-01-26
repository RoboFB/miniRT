/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:38:37 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: same: 0 not same: bigger or smaller | F: s1 == s2 until (n) uses bytes
int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			idx;
	unsigned char	*val_1;
	unsigned char	*val_2;

	val_1 = (unsigned char *)s1;
	val_2 = (unsigned char *)s2;
	idx = 0;
	if (n == 0)
		return (0);
	while (val_1[idx] == val_2[idx] && idx < n - 1)
		idx++;
	return ((int)((unsigned char)val_1[idx] - (unsigned char)val_2[idx]));
}
