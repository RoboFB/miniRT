/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_prf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 16:54:27 by rgohrig           #+#    #+#             */
/*   Updated: 2025/04/04 12:56:06 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_prf_str(char *str)
{
	int		idx;

	idx = 0;
	if (!str)
		str = "(null)";
	while (str[idx])
	{
		if (ft_prf_putchar(str[idx]) < 0)
			return (-1);
		idx++;
	}
	return (idx);
}
