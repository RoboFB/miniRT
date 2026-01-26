/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:53:24 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 14:27:26 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// use function f to make chance str char by char needs true str!
void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	idx;

	idx = 0;
	while (s[idx])
	{
		f(idx, s + idx);
		idx++;
	}
	return ;
}
