/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:21:37 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdio.h>

static char const	*ft_next_len(char const *p_next, char c, int *len);
static int			ft_count_words(char const *s, char c);
static int			ft_er_free_(char **pp_strs, int idx_words);

// F: Malloc R: map of the new splitted strs or NULL
char	**ft_split(char const *s, char c)
{
	char const		*position;
	int				len_substr;
	int				idx_words;
	char			**pp_split;

	idx_words = 0;
	position = s;
	pp_split = ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (pp_split == NULL)
		return (NULL);
	while (*position)
	{
		len_substr = 0;
		position = ft_next_len(position, c, &len_substr);
		if (!position)
			return (pp_split);
		if (len_substr)
		{
			pp_split[idx_words] = ft_substr(position, 0, len_substr);
			if (!ft_er_free_(pp_split, idx_words++))
				return (NULL);
			position += len_substr;
		}
	}
	return (pp_split);
}

static
char const	*ft_next_len(char const *p_next, char c, int *len)
{
	char const	*p_old;

	while (*p_next && *p_next == c)
		p_next++;
	p_old = p_next;
	while (*p_next && *p_next != c)
		p_next++;
	if (p_next > p_old)
	{
		*len = p_next - p_old;
		return (p_old);
	}
	else
		return (0);
}

static
int	ft_count_words(char const *s, char c)
{
	char const	*position;
	int			counter;
	int			len;

	counter = 0;
	len = 0;
	position = s;
	while (*position)
	{
		len = 0;
		position = ft_next_len(position, c, &len);
		if (!position && len)
			return (counter);
		else if (!position && !len)
			return (counter);
		position += len;
		counter++;
	}
	return (counter);
}

static int	ft_er_free_(char **pp_strs, int idx_words)
{
	int		idx;

	idx = 0;
	if (!pp_strs[idx_words])
	{
		while (idx < idx_words)
		{
			free(pp_strs[idx]);
			idx++;
		}
		free(pp_strs);
		return (0);
	}
	else
		return (1);
}
