/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prf_int_uint.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:45:51 by rgohrig           #+#    #+#             */
/*   Updated: 2025/06/24 14:49:07 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static
int	ft_prf_base10(int nbr)
{
	if (0 <= nbr && nbr <= 9)
		return (ft_prf_putchar('0' + nbr));
	return (-1);
}

int	ft_prf_uint(unsigned int nbr, int written_chars)
{
	int		result;

	result = 0;
	if (nbr <= 9)
	{
		if (ft_prf_base10(nbr) < 0)
			return (-1);
		return (++written_chars);
	}
	result = ft_prf_uint(nbr / 10, written_chars);
	if (result < 0)
		return (-1);
	written_chars += result;
	if (ft_prf_base10(nbr % 10) < 0)
		return (-1);
	return (++written_chars);
}

int	ft_prf_int(int nbr, int written_chars)
{
	int				result;
	unsigned int	positive_nbr;

	positive_nbr = nbr;
	if (nbr < 0)
	{
		if (ft_prf_putchar('-') < 0)
			return (-1);
		written_chars++;
		positive_nbr = (unsigned int)(nbr * -1);
	}
	result = ft_prf_uint(positive_nbr, 0);
	if (result < 0)
		return (-1);
	return (written_chars += result);
}
