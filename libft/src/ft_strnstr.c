/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:48:09 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: pointer to start of little in big or NULL or *big if little empty true str
// F: find (little) in (big) until (len)
char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	idx_big;
	size_t	idx_lit;

	idx_big = 0;
	if (!*little)
		return ((char *)big);
	while (big[idx_big] && idx_big < len)
	{
		idx_lit = 0;
		while (big[idx_big + idx_lit] && little[idx_lit]
			&& big[idx_big + idx_lit] == little[idx_lit]
			&& (idx_big + idx_lit) < len)
		{
			idx_lit++;
		}
		if (!little[idx_lit])
			return ((char *)big + idx_big);
		idx_big++;
	}
	return (NULL);
}
