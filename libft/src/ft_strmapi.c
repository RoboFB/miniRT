/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:28 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:26:11 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc R: str or NULL  | use function f to make new str char by char
char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	unsigned int	idx;
	char			*str;

	idx = 0;
	str = ft_calloc(ft_strlen(s) + 1, sizeof(char));
	if (!str)
		return (NULL);
	while (s[idx])
	{
		str[idx] = f(idx, s[idx]);
		idx++;
	}
	return (str);
}
