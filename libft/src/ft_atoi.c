/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/10 11:18:21 by rgohrig           #+#    #+#             */
/*   Updated: 2025/03/31 13:51:15 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// converts str to number
int	ft_atoi(const char *nptr)
{
	int		num;
	int		negative;
	char	*position;

	num = 0;
	negative = 1;
	position = (char *) nptr;
	while (*position == ' ' || *position == '\f' || *position == '\n' \
			|| *position == '\r' || *position == '\t' || *position == '\v')
		position++;
	if (*position == '+')
		position++;
	else if (*position == '-')
	{
		negative = -1;
		position++;
	}
	while (*position >= '0' && *position <= '9')
	{
		num = num * 10 + (*position - '0') * negative;
		position++;
	}
	return (num);
}
