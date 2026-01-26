/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 12:51:41 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: void *b | E: set memory(b) to char(c) len times
void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*buffer;
	size_t			idx;

	buffer = (unsigned char *)b;
	idx = 0;
	while (idx < len)
	{
		buffer[idx] = (unsigned char)c;
		idx++;
	}
	return (b);
}
