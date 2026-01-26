/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:35 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:03:46 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc R: *new_substr or Null  | duplicates substr at (start) with (len)
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_substr;
	size_t		max_len;

	if (!s)
		return (NULL);
	if (ft_strlen(s) < start)
	{
		new_substr = ft_calloc(1, sizeof(char));
		if (new_substr == NULL)
			return (NULL);
	}
	else
	{
		max_len = ft_strlen(s + start);
		if (max_len > len)
			max_len = len;
		new_substr = ft_calloc(max_len + 1, sizeof(char));
		if (new_substr == NULL)
			return (NULL);
		ft_strlcpy(new_substr, s + start, max_len + 1);
	}
	return (new_substr);
}
