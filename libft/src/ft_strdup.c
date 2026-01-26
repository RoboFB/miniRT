/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 15:24:03 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:58:20 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// F: Malloc R: new *str or Null  | duplicates true str(s)
char	*ft_strdup(const char *s)
{
	char	*new_string;
	size_t	len;

	len = ft_strlen(s) + 1;
	new_string = ft_calloc(len, sizeof(char));
	if (new_string == NULL)
		return (NULL);
	ft_strlcpy(new_string, s, len);
	return (new_string);
}
