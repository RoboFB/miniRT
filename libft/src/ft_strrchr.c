/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:24:39 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: pointer to last c in s or NULL. needs true str!
char	*ft_strrchr(const char *s, int c)
{
	char	*find;

	find = (char *)s;
	while (*find != '\0')
		find++;
	if ((char)c == '\0')
		return (find);
	while (find != s)
	{
		find--;
		if (*find == (char)c)
			return (find);
	}
	return (NULL);
}
