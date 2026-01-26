/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:24:10 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: pointer to first c in s or NULL. needs true str!
char	*ft_strchr(const char *s, int c)
{
	char	*find;

	find = (char *)s;
	while (*find != '\0')
	{
		if (*find == (char)c)
			return (find);
		else
			find++;
	}
	if ((char)c == '\0')
		return (find);
	return (NULL);
}
