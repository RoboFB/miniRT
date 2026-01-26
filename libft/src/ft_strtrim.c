/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:32 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:16:08 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc R: *new_str or Null | remove all chars(set) in (s1) both directions
char	*ft_strtrim(char const *s1, char const *set)
{
	char	*p_start;
	char	*p_end;
	char	*p_trimmed;
	size_t	size_trimmed;

	p_start = (char *)s1;
	p_end = (char *)(s1 + ft_strlen(s1));
	while (*p_start && ft_strchr(set, *p_start))
		p_start++;
	if (!(*p_start))
		size_trimmed = 1;
	else
	{
		while (p_end > p_start && ft_strchr(set, *p_end))
			p_end--;
		size_trimmed = (size_t)(p_end - p_start + 2);
	}
	p_trimmed = ft_calloc(size_trimmed, sizeof(char));
	if (!p_trimmed)
		return (NULL);
	ft_strlcpy(p_trimmed, p_start, size_trimmed);
	return (p_trimmed);
}
