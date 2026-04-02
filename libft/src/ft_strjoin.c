/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:27 by rgohrig           #+#    #+#             */
/*   Updated: 2026/04/02 12:48:59 by rgohrig          ###   ########.fr       */
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

char	*ft_strjoin_3(char const *s1, char const *s2, char const *s3)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	if (s1_len > SIZE_MAX - s2_len - s3_len)
		return (NULL);
	join = ft_calloc(s1_len + s2_len + s3_len + 1, sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	ft_memcpy(join + s1_len + s2_len, s3, s3_len);
	return (join);
}

char	*ft_strjoin_4(char const *s1, char const *s2,
	char const *s3, char const *s4)
{
	char	*join;
	size_t	s1_len;
	size_t	s2_len;
	size_t	s3_len;
	size_t	s4_len;

	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	s3_len = ft_strlen(s3);
	s4_len = ft_strlen(s4);
	if (s1_len > SIZE_MAX - s2_len - s3_len - s4_len)
		return (NULL);
	join = ft_calloc(s1_len + s2_len + s3_len + s4_len + 1, sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, s1_len);
	ft_memcpy(join + s1_len, s2, s2_len);
	ft_memcpy(join + s1_len + s2_len, s3, s3_len);
	ft_memcpy(join + s1_len + s2_len + s3_len, s4, s4_len);
	return (join);
}
