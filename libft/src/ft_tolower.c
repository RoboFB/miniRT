/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:21:22 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// R: one character  | F: upercase to lowercase
int	ft_tolower(int c)
{
	if ('A' <= c && 'Z' >= c)
		c = (unsigned char)c + 32;
	return (c);
}
