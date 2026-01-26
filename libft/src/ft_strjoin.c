/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:27 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:06:12 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc R: *new_joined_str out of s1 and s2 or Null
char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	len_s1;
	size_t	total_size;
	char	*joined_str;

	len_s1 = ft_strlen(s1);
	total_size = len_s1 + ft_strlen(s2) + 1;
	joined_str = ft_calloc(total_size, sizeof(char));
	if (joined_str == NULL)
		return (NULL);
	ft_strlcpy(joined_str, s1, total_size);
	ft_strlcpy(joined_str + len_s1, s2, total_size - len_s1);
	return (joined_str);
}
