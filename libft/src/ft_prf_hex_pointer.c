/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_prf_hex_pointer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rgohrig <rgohrig@student.42heilbronn.de>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 18:45:45 by rgohrig           #+#    #+#             */
/*   Updated: 2025/06/24 14:49:30 by rgohrig          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static
int	ft_prt_base16(int nbr, char letter_start)
{
	if (0 <= nbr && nbr <= 9)
		return (ft_prf_putchar('0' + nbr));
	else if (10 <= nbr && nbr <= 15)
		return (ft_prf_putchar(letter_start + nbr - 10));
	return (-1);
}

int	ft_prf_hex(unsigned int nbr, char letter_start, int written_chars)
{
	int		result;

	result = 0;
	if (nbr <= 15)
	{
		if (ft_prt_base16(nbr, letter_start) < 0)
			return (-1);
		return (++written_chars);
	}
	result = ft_prf_hex(nbr / 16, letter_start, written_chars);
	if (result < 0)
		return (-1);
	written_chars += result;
	if (ft_prt_base16(nbr % 16, letter_start) < 0)
		return (-1);
	return (++written_chars);
}

int	ft_prf_pointer(uintptr_t nbr, char letter_start, int written_chars)
{
	int		result;

	result = 0;
	if (nbr <= 15)
	{
		result = ft_prf_str("0x");
		if (result < 0)
			return (-1);
		written_chars += result;
		if (ft_prt_base16(nbr, letter_start) < 0)
			return (-1);
		return (++written_chars);
	}
	result = ft_prf_pointer(nbr / 16, letter_start, written_chars);
	if (result < 0)
		return (-1);
	written_chars += result;
	if (ft_prt_base16(nbr % 16, letter_start) < 0)
		return (-1);
	return (++written_chars);
}
